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
struct lz_range_decoder {int dummy; } ;

/* Variables and functions */
 unsigned int lz_rd_decode_tree (struct lz_range_decoder*,int*,int) ; 

__attribute__((used)) static unsigned
lz_rd_decode_tree_reversed(struct lz_range_decoder *rd, int *bm, int num_bits)
{
	unsigned symbol = lz_rd_decode_tree(rd, bm, num_bits);
	unsigned reversed_symbol = 0;

	for (int i = 0; i < num_bits; i++) {
		reversed_symbol = (reversed_symbol << 1) | (symbol & 1);
		symbol >>= 1;
	}

	return reversed_symbol;
}