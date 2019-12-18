#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  MS_SYNC ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  get_symbols (char const*,void*) ; 
 void* map_vdso (char const*,size_t*) ; 
 scalar_t__ msync (void*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_file ; 
 int /*<<< orphan*/  patch_vdso (char const*,void*) ; 
 char* program_name ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink (char const*) ; 
 char* vdso_name ; 

int main(int argc, char **argv)
{
	const char *dbg_vdso_path, *vdso_path, *out_path;
	void *dbg_vdso, *vdso;
	size_t dbg_vdso_size, vdso_size, i;

	program_name = argv[0];

	if (argc < 4 || argc > 5) {
		fprintf(stderr,
			"Usage: %s <debug VDSO> <stripped VDSO> <output file> [<name>]\n",
			program_name);
		return EXIT_FAILURE;
	}

	dbg_vdso_path = argv[1];
	vdso_path = argv[2];
	out_path = argv[3];
	vdso_name = (argc > 4) ? argv[4] : "";

	dbg_vdso = map_vdso(dbg_vdso_path, &dbg_vdso_size);
	if (!dbg_vdso)
		return EXIT_FAILURE;

	vdso = map_vdso(vdso_path, &vdso_size);
	if (!vdso)
		return EXIT_FAILURE;

	/* Patch both the VDSOs' ABI flags sections. */
	if (!patch_vdso(dbg_vdso_path, dbg_vdso))
		return EXIT_FAILURE;
	if (!patch_vdso(vdso_path, vdso))
		return EXIT_FAILURE;

	if (msync(dbg_vdso, dbg_vdso_size, MS_SYNC) != 0) {
		fprintf(stderr, "%s: Failed to sync '%s': %s\n", program_name,
			dbg_vdso_path, strerror(errno));
		return EXIT_FAILURE;
	} else if (msync(vdso, vdso_size, MS_SYNC) != 0) {
		fprintf(stderr, "%s: Failed to sync '%s': %s\n", program_name,
			vdso_path, strerror(errno));
		return EXIT_FAILURE;
	}

	out_file = fopen(out_path, "w");
	if (!out_file) {
		fprintf(stderr, "%s: Failed to open '%s': %s\n", program_name,
			out_path, strerror(errno));
		return EXIT_FAILURE;
	}

	fprintf(out_file, "/* Automatically generated - do not edit */\n");
	fprintf(out_file, "#include <linux/linkage.h>\n");
	fprintf(out_file, "#include <linux/mm.h>\n");
	fprintf(out_file, "#include <asm/vdso.h>\n");

	/* Write out the stripped VDSO data. */
	fprintf(out_file,
		"static unsigned char vdso_data[PAGE_ALIGN(%zu)] __page_aligned_data = {\n\t",
		vdso_size);
	for (i = 0; i < vdso_size; i++) {
		if (!(i % 10))
			fprintf(out_file, "\n\t");
		fprintf(out_file, "0x%02x, ", ((unsigned char *)vdso)[i]);
	}
	fprintf(out_file, "\n};\n");

	/* Preallocate a page array. */
	fprintf(out_file,
		"static struct page *vdso_pages[PAGE_ALIGN(%zu) / PAGE_SIZE];\n",
		vdso_size);

	fprintf(out_file, "struct mips_vdso_image vdso_image%s%s = {\n",
		(vdso_name[0]) ? "_" : "", vdso_name);
	fprintf(out_file, "\t.data = vdso_data,\n");
	fprintf(out_file, "\t.size = PAGE_ALIGN(%zu),\n", vdso_size);
	fprintf(out_file, "\t.mapping = {\n");
	fprintf(out_file, "\t\t.name = \"[vdso]\",\n");
	fprintf(out_file, "\t\t.pages = vdso_pages,\n");
	fprintf(out_file, "\t},\n");

	/* Calculate and write symbol offsets to <output file> */
	if (!get_symbols(dbg_vdso_path, dbg_vdso)) {
		unlink(out_path);
		return EXIT_FAILURE;
	}

	fprintf(out_file, "};\n");

	return EXIT_SUCCESS;
}