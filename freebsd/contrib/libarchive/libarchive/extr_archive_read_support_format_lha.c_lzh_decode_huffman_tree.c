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
struct huffman {int shift_bits; int len_avail; int tree_used; struct htree_t* tree; } ;
struct htree_t {int left; int right; } ;

/* Variables and functions */

__attribute__((used)) static int
lzh_decode_huffman_tree(struct huffman *hf, unsigned rbits, int c)
{
	struct htree_t *ht;
	int extlen;

	ht = hf->tree;
	extlen = hf->shift_bits;
	while (c >= hf->len_avail) {
		c -= hf->len_avail;
		if (extlen-- <= 0 || c >= hf->tree_used)
			return (0);
		if (rbits & (1U << extlen))
			c = ht[c].left;
		else
			c = ht[c].right;
	}
	return (c);
}