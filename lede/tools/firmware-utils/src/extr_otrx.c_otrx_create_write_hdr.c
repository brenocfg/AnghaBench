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
typedef  int uint32_t ;
struct trx_header {int version; void* crc32; int /*<<< orphan*/  length; void* magic; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ TRX_FLAGS_OFFSET ; 
 int TRX_MAGIC ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 size_t fread (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 size_t fwrite (struct trx_header*,int,int,int /*<<< orphan*/ *) ; 
 size_t le32_to_cpu (int /*<<< orphan*/ ) ; 
 int otrx_crc32 (int,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  otrx_min (int,size_t) ; 
 int /*<<< orphan*/  stderr ; 
 char* trx_path ; 

__attribute__((used)) static int otrx_create_write_hdr(FILE *trx, struct trx_header *hdr) {
	size_t bytes, length;
	uint8_t buf[1024];
	uint32_t crc32;

	hdr->magic = cpu_to_le32(TRX_MAGIC);
	hdr->version = 1;

	fseek(trx, 0, SEEK_SET);
	bytes = fwrite(hdr, 1, sizeof(struct trx_header), trx);
	if (bytes != sizeof(struct trx_header)) {
		fprintf(stderr, "Couldn't write TRX header to %s\n", trx_path);
		return -EIO;
	}

	length = le32_to_cpu(hdr->length);

	crc32 = 0xffffffff;
	fseek(trx, TRX_FLAGS_OFFSET, SEEK_SET);
	length -= TRX_FLAGS_OFFSET;
	while ((bytes = fread(buf, 1, otrx_min(sizeof(buf), length), trx)) > 0) {
		crc32 = otrx_crc32(crc32, buf, bytes);
		length -= bytes;
	}
	hdr->crc32 = cpu_to_le32(crc32);

	fseek(trx, 0, SEEK_SET);
	bytes = fwrite(hdr, 1, sizeof(struct trx_header), trx);
	if (bytes != sizeof(struct trx_header)) {
		fprintf(stderr, "Couldn't write TRX header to %s\n", trx_path);
		return -EIO;
	}

	return 0;
}