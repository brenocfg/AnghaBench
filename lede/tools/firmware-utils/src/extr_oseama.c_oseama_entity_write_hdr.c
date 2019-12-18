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
typedef  int /*<<< orphan*/  uint8_t ;
struct seama_entity_header {void* imagesize; int /*<<< orphan*/  metasize; void* magic; int /*<<< orphan*/  md5; } ;
typedef  int /*<<< orphan*/  hdr ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  MD5_CTX ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  MD5_Final (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5_Update (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 size_t SEAMA_MAGIC ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  cpu_to_be16 (size_t) ; 
 void* cpu_to_be32 (size_t) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 size_t fread (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 size_t fwrite (struct seama_entity_header*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oseama_min (int,size_t) ; 
 char* seama_path ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int oseama_entity_write_hdr(FILE *seama, size_t metasize, size_t imagesize) {
	struct seama_entity_header hdr = {};
	uint8_t buf[128];
	size_t length = imagesize;
	size_t bytes;
	MD5_CTX ctx;

	fseek(seama, sizeof(hdr) + metasize, SEEK_SET);
	MD5_Init(&ctx);
	while ((bytes = fread(buf, 1, oseama_min(sizeof(buf), length), seama)) > 0) {
		MD5_Update(&ctx, buf, bytes);
		length -= bytes;
	}
	MD5_Final(hdr.md5, &ctx);

	hdr.magic = cpu_to_be32(SEAMA_MAGIC);
	hdr.metasize = cpu_to_be16(metasize);
	hdr.imagesize = cpu_to_be32(imagesize);

	fseek(seama, 0, SEEK_SET);
	bytes = fwrite(&hdr, 1, sizeof(hdr), seama);
	if (bytes != sizeof(hdr)) {
		fprintf(stderr, "Couldn't write Seama entity header to %s\n", seama_path);
		return -EIO;
	}

	return 0;
}