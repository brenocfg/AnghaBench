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
typedef  scalar_t__ uint16_t ;
struct huffman {int* freq; int tbl_bits; int max_bits; unsigned char* bitlen; int len_size; scalar_t__ tree_used; scalar_t__* tbl; } ;

/* Variables and functions */

__attribute__((used)) static int
lzx_make_huffman_table(struct huffman *hf)
{
	uint16_t *tbl;
	const unsigned char *bitlen;
	int bitptn[17], weight[17];
	int i, maxbits = 0, ptn, tbl_size, w;
	int len_avail;

	/*
	 * Initialize bit patterns.
	 */
	ptn = 0;
	for (i = 1, w = 1 << 15; i <= 16; i++, w >>= 1) {
		bitptn[i] = ptn;
		weight[i] = w;
		if (hf->freq[i]) {
			ptn += hf->freq[i] * w;
			maxbits = i;
		}
	}
	if ((ptn & 0xffff) != 0 || maxbits > hf->tbl_bits)
		return (0);/* Invalid */

	hf->max_bits = maxbits;

	/*
	 * Cut out extra bits which we won't house in the table.
	 * This preparation reduces the same calculation in the for-loop
	 * making the table.
	 */
	if (maxbits < 16) {
		int ebits = 16 - maxbits;
		for (i = 1; i <= maxbits; i++) {
			bitptn[i] >>= ebits;
			weight[i] >>= ebits;
		}
	}

	/*
	 * Make the table.
	 */
	tbl_size = 1 << hf->tbl_bits;
	tbl = hf->tbl;
	bitlen = hf->bitlen;
	len_avail = hf->len_size;
	hf->tree_used = 0;
	for (i = 0; i < len_avail; i++) {
		uint16_t *p;
		int len, cnt;

		if (bitlen[i] == 0)
			continue;
		/* Get a bit pattern */
		len = bitlen[i];
		if (len > tbl_size)
			return (0);
		ptn = bitptn[len];
		cnt = weight[len];
		/* Calculate next bit pattern */
		if ((bitptn[len] = ptn + cnt) > tbl_size)
			return (0);/* Invalid */
		/* Update the table */
		p = &(tbl[ptn]);
		while (--cnt >= 0)
			p[cnt] = (uint16_t)i;
	}
	return (1);
}