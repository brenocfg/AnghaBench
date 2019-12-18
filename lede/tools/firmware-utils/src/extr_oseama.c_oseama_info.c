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
struct seama_seal_header {int /*<<< orphan*/  magic; int /*<<< orphan*/  imagesize; int /*<<< orphan*/  metasize; } ;
typedef  struct seama_seal_header uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  hdr ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EACCES ; 
 int EINVAL ; 
 int EIO ; 
 int SEAMA_MAGIC ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ entity_idx ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 size_t fread (struct seama_seal_header*,int,int,int /*<<< orphan*/ *) ; 
 int optind ; 
 int /*<<< orphan*/  oseama_info_entities (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oseama_info_parse_options (int,char**) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* seama_path ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static int oseama_info(int argc, char **argv) {
	FILE *seama;
	struct seama_seal_header hdr;
	size_t bytes;
	uint16_t metasize;
	uint32_t imagesize;
	uint8_t buf[1024];
	int err = 0;

	if (argc < 3) {
		fprintf(stderr, "No Seama file passed\n");
		err = -EINVAL;
		goto out;
	}
	seama_path = argv[2];

	optind = 3;
	oseama_info_parse_options(argc, argv);

	seama = fopen(seama_path, "r");
	if (!seama) {
		fprintf(stderr, "Couldn't open %s\n", seama_path);
		err = -EACCES;
		goto out;
	}

	bytes = fread(&hdr, 1, sizeof(hdr), seama);
	if (bytes != sizeof(hdr)) {
		fprintf(stderr, "Couldn't read %s header\n", seama_path);
		err =  -EIO;
		goto err_close;
	}
	metasize = be16_to_cpu(hdr.metasize);
	imagesize = be32_to_cpu(hdr.imagesize);

	if (be32_to_cpu(hdr.magic) != SEAMA_MAGIC) {
		fprintf(stderr, "Invalid Seama magic: 0x%08x\n", be32_to_cpu(hdr.magic));
		err =  -EINVAL;
		goto err_close;
	}

	if (metasize >= sizeof(buf)) {
		fprintf(stderr, "Too small buffer (%zu B) to read all meta info (%d B)\n", sizeof(buf), metasize);
		err =  -EINVAL;
		goto err_close;
	}

	if (imagesize) {
		fprintf(stderr, "Invalid Seama image size: 0x%08x (should be 0)\n", imagesize);
		err =  -EINVAL;
		goto err_close;
	}

	bytes = fread(buf, 1, metasize, seama);
	if (bytes != metasize) {
		fprintf(stderr, "Couldn't read %d B of meta\n", metasize);
		err =  -EIO;
		goto err_close;
	}

	if (entity_idx < 0) {
		char *end, *tmp;

		printf("Meta size:\t%d\n", metasize);
		printf("Image size:\t%d\n", imagesize);

		end = (char *)&buf[metasize - 1];
		*end = '\0';
		for (tmp = (char *)buf; tmp < end && strlen(tmp); tmp += strlen(tmp) + 1) {
			printf("Meta entry:\t%s\n", tmp);
		}
	}

	oseama_info_entities(seama);

err_close:
	fclose(seama);
out:
	return err;
}