#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct trx_header {scalar_t__ magic; int* offsets; } ;
struct TYPE_3__ {int /*<<< orphan*/  Read; } ;
typedef  TYPE_1__ ILzmaInCallback ;

/* Variables and functions */
 int /*<<< orphan*/  BCM4710_FLASH ; 
 int /*<<< orphan*/  EDIMAX_PS_HEADER_LEN ; 
 scalar_t__ EDIMAX_PS_HEADER_MAGIC ; 
 scalar_t__ KSEG1ADDR (int /*<<< orphan*/ ) ; 
 scalar_t__ LOADADDR ; 
 scalar_t__ LZMA_RESULT_OK ; 
 scalar_t__ LzmaDecode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int,TYPE_1__*,unsigned char*,unsigned int,unsigned int*) ; 
 scalar_t__ TRX_MAGIC ; 
 int /*<<< orphan*/  blast_dcache (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  blast_icache (unsigned long,unsigned long) ; 
 unsigned char* data ; 
 unsigned int get_byte () ; 
 scalar_t__ offset ; 
 int /*<<< orphan*/  read_byte ; 
 void stub1 (unsigned long,unsigned long,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  workspace ; 

void entry(unsigned long icache_size, unsigned long icache_lsize, 
	unsigned long dcache_size, unsigned long dcache_lsize,
	unsigned long fw_arg0, unsigned long fw_arg1,
	unsigned long fw_arg2, unsigned long fw_arg3)
{
	unsigned int i;  /* temp value */
	unsigned int lc; /* literal context bits */
	unsigned int lp; /* literal pos state bits */
	unsigned int pb; /* pos state bits */
	unsigned int osize; /* uncompressed size */

	ILzmaInCallback callback;
	callback.Read = read_byte;

	/* look for trx header, 32-bit data access */
	for (data = ((unsigned char *) KSEG1ADDR(BCM4710_FLASH));
		((struct trx_header *)data)->magic != TRX_MAGIC &&
		((struct trx_header *)data)->magic != EDIMAX_PS_HEADER_MAGIC;
		 data += 65536);

	if (((struct trx_header *)data)->magic == EDIMAX_PS_HEADER_MAGIC)
		data += EDIMAX_PS_HEADER_LEN;
	/* compressed kernel is in the partition 0 or 1 */
	if (((struct trx_header *)data)->offsets[1] > 65536) 
		data += ((struct trx_header *)data)->offsets[0];
	else
		data += ((struct trx_header *)data)->offsets[1];

	offset = 0;

	/* lzma args */
	i = get_byte();
	lc = i % 9, i = i / 9;
	lp = i % 5, pb = i / 5;

	/* skip rest of the LZMA coder property */
	for (i = 0; i < 4; i++)
		get_byte();

	/* read the lower half of uncompressed size in the header */
	osize = ((unsigned int)get_byte()) +
		((unsigned int)get_byte() << 8) +
		((unsigned int)get_byte() << 16) +
		((unsigned int)get_byte() << 24);

	/* skip rest of the header (upper half of uncompressed size) */
	for (i = 0; i < 4; i++) 
		get_byte();

	/* decompress kernel */
	if (LzmaDecode(workspace, ~0, lc, lp, pb, &callback,
		(unsigned char*)LOADADDR, osize, &i) == LZMA_RESULT_OK)
	{
		blast_dcache(dcache_size, dcache_lsize);
		blast_icache(icache_size, icache_lsize);

		/* Jump to load address */
		((void (*)(unsigned long, unsigned long, unsigned long,
			unsigned long)) LOADADDR)(fw_arg0, fw_arg1, fw_arg2,
				fw_arg3);
	}
}