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
typedef  int /*<<< orphan*/  zio_cksum_t ;
typedef  int uint8_t ;
typedef  int uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SHA256Transform (int*,int*) ; 
 int /*<<< orphan*/  ZIO_SET_CHECKSUM (int /*<<< orphan*/ *,int,int,int,int) ; 

__attribute__((used)) static void
SHA256(uint32_t *H, const void *buf, uint64_t size, zio_cksum_t *zcp)
{
	uint8_t pad[128];
	unsigned padsize = size & 63;
	unsigned i, k;

	/* process all blocks up to the last one */
	for (i = 0; i < size - padsize; i += 64)
		SHA256Transform(H, (uint8_t *)buf + i);

	/* process the last block and padding */
	for (k = 0; k < padsize; k++)
		pad[k] = ((uint8_t *)buf)[k+i];

	for (pad[padsize++] = 0x80; (padsize & 63) != 56; padsize++)
		pad[padsize] = 0;

	for (i = 0; i < 8; i++)
		pad[padsize++] = (size << 3) >> (56 - 8 * i);

	for (i = 0; i < padsize; i += 64)
		SHA256Transform(H, pad + i);

	ZIO_SET_CHECKSUM(zcp,
	    (uint64_t)H[0] << 32 | H[1],
	    (uint64_t)H[2] << 32 | H[3],
	    (uint64_t)H[4] << 32 | H[5],
	    (uint64_t)H[6] << 32 | H[7]);
}