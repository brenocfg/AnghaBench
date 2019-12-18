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
typedef  int /*<<< orphan*/  c64 ;

/* Variables and functions */
 int /*<<< orphan*/  Encode64 (int*,int*,int) ; 
 int /*<<< orphan*/  SHA512Transform (int*,int*) ; 

__attribute__((used)) static void
SHA512(uint64_t *H, const void *buf, uint64_t size, zio_cksum_t *zcp)
{
	uint64_t	c64[2];
	uint8_t		pad[256];
	unsigned	padsize = size & 127;
	unsigned	i, k;

	/* process all blocks up to the last one */
	for (i = 0; i < size - padsize; i += 128)
		SHA512Transform(H, (uint8_t *)buf + i);

	/* process the last block and padding */
	for (k = 0; k < padsize; k++)
		pad[k] = ((uint8_t *)buf)[k+i];

	if (padsize < 112) {
		for (pad[padsize++] = 0x80; padsize < 112; padsize++)
			pad[padsize] = 0;
	} else {
		for (pad[padsize++] = 0x80; padsize < 240; padsize++)
			pad[padsize] = 0;
	}

	c64[0] = 0;
	c64[1] = size << 3;
	Encode64(pad+padsize, c64, sizeof (c64));
	padsize += sizeof (c64);

	for (i = 0; i < padsize; i += 128)
		SHA512Transform(H, pad + i);

	/* truncate the output to the first 256 bits which fit into 'zcp' */
	Encode64((uint8_t *)zcp, H, sizeof (uint64_t) * 4);
}