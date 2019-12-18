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
struct seama_entity_header {int /*<<< orphan*/  imagesize; int /*<<< orphan*/  metasize; int /*<<< orphan*/  magic; } ;
typedef  struct seama_entity_header uint8_t ;
typedef  int /*<<< orphan*/  hdr ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int SEAMA_MAGIC ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 size_t be16_to_cpu (int /*<<< orphan*/ ) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int entity_idx ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,size_t,...) ; 
 size_t fread (struct seama_entity_header*,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 char* ftell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static int oseama_info_entities(FILE *seama) {
	struct seama_entity_header hdr;
	size_t bytes, metasize, imagesize;
	uint8_t buf[1024];
	char *end, *tmp;
	int i = 0;
	int err = 0;

	while ((bytes = fread(&hdr, 1, sizeof(hdr), seama)) == sizeof(hdr)) {
		if (be32_to_cpu(hdr.magic) != SEAMA_MAGIC) {
			fprintf(stderr, "Invalid Seama magic: 0x%08x\n", be32_to_cpu(hdr.magic));
			err =  -EINVAL;
			goto err_out;
		}
		metasize = be16_to_cpu(hdr.metasize);
		imagesize = be32_to_cpu(hdr.imagesize);

		if (entity_idx >= 0 && i != entity_idx) {
			fseek(seama, metasize + imagesize, SEEK_CUR);
			i++;
			continue;
		}

		if (metasize >= sizeof(buf)) {
			fprintf(stderr, "Too small buffer (%zu B) to read all meta info (%zd B)\n", sizeof(buf), metasize);
			err =  -EINVAL;
			goto err_out;
		}

		if (entity_idx < 0)
			printf("\n");
		printf("Entity offset:\t%ld\n", ftell(seama) - sizeof(hdr));
		printf("Entity size:\t%zd\n", sizeof(hdr) + metasize + imagesize);
		printf("Meta size:\t%zd\n", metasize);
		printf("Image size:\t%zd\n", imagesize);

		bytes = fread(buf, 1, metasize, seama);
		if (bytes != metasize) {
			fprintf(stderr, "Couldn't read %zd B of meta\n", metasize);
			err =  -EIO;
			goto err_out;
		}

		end = (char *)&buf[metasize - 1];
		*end = '\0';
		for (tmp = (char *)buf; tmp < end && strlen(tmp); tmp += strlen(tmp) + 1) {
			printf("Meta entry:\t%s\n", tmp);
		}

		fseek(seama, imagesize, SEEK_CUR);
		i++;
	}

err_out:
	return err;
}