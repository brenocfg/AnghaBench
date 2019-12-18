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
typedef  int /*<<< orphan*/  uint16_t ;
struct seama_seal_header {int /*<<< orphan*/  metasize; } ;
typedef  int /*<<< orphan*/  hdr ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EACCES ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ entity_idx ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 size_t fread (struct seama_seal_header*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int optind ; 
 int /*<<< orphan*/  oseama_extract_entity (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oseama_extract_parse_options (int,char**) ; 
 char* out_path ; 
 char* seama_path ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int oseama_extract(int argc, char **argv) {
	FILE *seama;
	FILE *out;
	struct seama_seal_header hdr;
	size_t bytes;
	uint16_t metasize;
	int err = 0;

	if (argc < 3) {
		fprintf(stderr, "No Seama file passed\n");
		err = -EINVAL;
		goto out;
	}
	seama_path = argv[2];

	optind = 3;
	oseama_extract_parse_options(argc, argv);
	if (entity_idx < 0) {
		fprintf(stderr, "No entity specified\n");
		err = -EINVAL;
		goto out;
	} else if (!out_path) {
		fprintf(stderr, "No output file specified\n");
		err = -EINVAL;
		goto out;
	}

	seama = fopen(seama_path, "r");
	if (!seama) {
		fprintf(stderr, "Couldn't open %s\n", seama_path);
		err = -EACCES;
		goto out;
	}

	out = fopen(out_path, "w");
	if (!out) {
		fprintf(stderr, "Couldn't open %s\n", out_path);
		err = -EACCES;
		goto err_close_seama;
	}

	bytes = fread(&hdr, 1, sizeof(hdr), seama);
	if (bytes != sizeof(hdr)) {
		fprintf(stderr, "Couldn't read %s header\n", seama_path);
		err =  -EIO;
		goto err_close_out;
	}
	metasize = be16_to_cpu(hdr.metasize);

	fseek(seama, metasize, SEEK_CUR);

	oseama_extract_entity(seama, out);

err_close_out:
	fclose(out);
err_close_seama:
	fclose(seama);
out:
	return err;
}