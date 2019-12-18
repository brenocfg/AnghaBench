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
struct trx_header {int /*<<< orphan*/  len; int /*<<< orphan*/ * offsets; } ;

/* Variables and functions */
 size_t FLASH_BANK_SIZE ; 
 scalar_t__ TRX_ALIGN ; 
 unsigned long TRX_MAGIC ; 
 int /*<<< orphan*/ * flash_base ; 
 size_t flash_max ; 
 size_t flash_ofs ; 
 int /*<<< orphan*/  halt () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 unsigned long read_le32 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void decompress_init(void)
{
	struct trx_header *hdr = NULL;
	unsigned long kofs,klen;

    	printf("Looking for TRX header... ");
	/* look for trx header, 32-bit data access */
	for (flash_ofs = 0; flash_ofs < FLASH_BANK_SIZE; flash_ofs += TRX_ALIGN) {
		if (read_le32(&flash_base[flash_ofs]) == TRX_MAGIC) {
			hdr = (struct trx_header *)&flash_base[flash_ofs];
			break;
		}
	}

	if (hdr == NULL) {
		printf("not found!\n");
		/* no compressed kernel found, halting */
		halt();
	}

	/* compressed kernel is in the partition 0 or 1 */
	kofs = read_le32(&hdr->offsets[1]);
	if (kofs == 0 || kofs > 65536) {
		klen = kofs-read_le32(&hdr->offsets[0]);
		kofs = read_le32(&hdr->offsets[0]);
	} else {
		klen = read_le32(&hdr->offsets[2]);
		if (klen > kofs)
			klen -= kofs;
		else
			klen = read_le32(&hdr->len)-kofs;
	}

	printf("found at %08X, kernel:%08X len:%08X\n", flash_ofs,
		kofs, klen);

	flash_ofs += kofs;
	flash_max = flash_ofs+klen;
}