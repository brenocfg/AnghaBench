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
struct safeloader_header {int dummy; } ;
typedef  struct safeloader_header uint8_t ;
typedef  int /*<<< orphan*/  hdr ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EACCES ; 
 int EINVAL ; 
 int EIO ; 
 int ENOENT ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 size_t fread (struct safeloader_header*,int,int,int /*<<< orphan*/ *) ; 
 int fscanf (int /*<<< orphan*/ *,char*,char*,int*,int*) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 size_t fwrite (struct safeloader_header*,int,size_t,int /*<<< orphan*/ *) ; 
 int optind ; 
 int /*<<< orphan*/  osafeloader_extract_parse_options (int,char**) ; 
 int osafeloader_min (int,int) ; 
 char* out_path ; 
 char* partition_name ; 
 char* safeloader_path ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int osafeloader_extract(int argc, char **argv) {
	FILE *safeloader;
	FILE *out;
	struct safeloader_header hdr;
	size_t bytes;
	char name[32];
	int base, size;
	int err = 0;

	if (argc < 3) {
		fprintf(stderr, "No SafeLoader file passed\n");
		err = -EINVAL;
		goto out;
	}
	safeloader_path = argv[2];

	optind = 3;
	osafeloader_extract_parse_options(argc, argv);
	if (!partition_name) {
		fprintf(stderr, "No partition name specified\n");
		err = -EINVAL;
		goto out;
	} else if (!out_path) {
		fprintf(stderr, "No output file specified\n");
		err = -EINVAL;
		goto out;
	}

	safeloader = fopen(safeloader_path, "r");
	if (!safeloader) {
		fprintf(stderr, "Couldn't open %s\n", safeloader_path);
		err = -EACCES;
		goto out;
	}

	out = fopen(out_path, "w");
	if (!out) {
		fprintf(stderr, "Couldn't open %s\n", out_path);
		err = -EACCES;
		goto err_close_safeloader;
	}

	bytes = fread(&hdr, 1, sizeof(hdr), safeloader);
	if (bytes != sizeof(hdr)) {
		fprintf(stderr, "Couldn't read %s header\n", safeloader_path);
		err =  -EIO;
		goto err_close_out;
	}

	/* Skip vendor info */
	fseek(safeloader, 0x1000, SEEK_CUR);

	err = -ENOENT;
	while (fscanf(safeloader, "fwup-ptn %s base 0x%x size 0x%x\t\r\n", name, &base, &size) == 3) {
		uint8_t buf[1024];

		if (strcmp(name, partition_name))
			continue;

		err = 0;

		fseek(safeloader, sizeof(hdr) + 0x1000 + base, SEEK_SET);

		while ((bytes = fread(buf, 1, osafeloader_min(sizeof(buf), size), safeloader)) > 0) {
			if (fwrite(buf, 1, bytes, out) != bytes) {
				fprintf(stderr, "Couldn't write %zu B to %s\n", bytes, out_path);
				err = -EIO;
				break;
			}
			size -= bytes;
		}

		if (size) {
			fprintf(stderr, "Couldn't extract whole partition %s from %s (%d B left)\n", partition_name, safeloader_path, size);
			err = -EIO;
		}

		break;
	}

err_close_out:
	fclose(out);
err_close_safeloader:
	fclose(safeloader);
out:
	return err;
}