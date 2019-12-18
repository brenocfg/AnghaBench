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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t EI_CLASS ; 
 int EI_NIDENT ; 
 unsigned char ELFCLASS64 ; 
 int /*<<< orphan*/  die (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int fread (unsigned char**,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  process_32 (int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  process_64 (int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 

int main(int argc, char **argv)
{
	int show_reloc_info, as_text, as_bin, keep_relocs;
	const char *fname;
	FILE *fp;
	int i;
	unsigned char e_ident[EI_NIDENT];

	show_reloc_info = 0;
	as_text = 0;
	as_bin = 0;
	keep_relocs = 0;
	fname = NULL;
	for (i = 1; i < argc; i++) {
		char *arg = argv[i];

		if (*arg == '-') {
			if (strcmp(arg, "--reloc-info") == 0) {
				show_reloc_info = 1;
				continue;
			}
			if (strcmp(arg, "--text") == 0) {
				as_text = 1;
				continue;
			}
			if (strcmp(arg, "--bin") == 0) {
				as_bin = 1;
				continue;
			}
			if (strcmp(arg, "--keep") == 0) {
				keep_relocs = 1;
				continue;
			}
		} else if (!fname) {
			fname = arg;
			continue;
		}
		usage();
	}
	if (!fname)
		usage();

	fp = fopen(fname, "r+");
	if (!fp)
		die("Cannot open %s: %s\n", fname, strerror(errno));

	if (fread(&e_ident, 1, EI_NIDENT, fp) != EI_NIDENT)
		die("Cannot read %s: %s", fname, strerror(errno));

	rewind(fp);
	if (e_ident[EI_CLASS] == ELFCLASS64)
		process_64(fp, as_text,  as_bin, show_reloc_info, keep_relocs);
	else
		process_32(fp, as_text, as_bin, show_reloc_info, keep_relocs);
	fclose(fp);
	return 0;
}