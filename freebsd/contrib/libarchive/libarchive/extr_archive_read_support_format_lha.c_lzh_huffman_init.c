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
struct huffman {int tree_avail; int len_size; int tbl_bits; int /*<<< orphan*/ * tree; int /*<<< orphan*/ * tbl; int /*<<< orphan*/ * bitlen; } ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int HTBL_BITS ; 
 void* malloc (int) ; 

__attribute__((used)) static int
lzh_huffman_init(struct huffman *hf, size_t len_size, int tbl_bits)
{
	int bits;

	if (hf->bitlen == NULL) {
		hf->bitlen = malloc(len_size * sizeof(hf->bitlen[0]));
		if (hf->bitlen == NULL)
			return (ARCHIVE_FATAL);
	}
	if (hf->tbl == NULL) {
		if (tbl_bits < HTBL_BITS)
			bits = tbl_bits;
		else
			bits = HTBL_BITS;
		hf->tbl = malloc(((size_t)1 << bits) * sizeof(hf->tbl[0]));
		if (hf->tbl == NULL)
			return (ARCHIVE_FATAL);
	}
	if (hf->tree == NULL && tbl_bits > HTBL_BITS) {
		hf->tree_avail = 1 << (tbl_bits - HTBL_BITS + 4);
		hf->tree = malloc(hf->tree_avail * sizeof(hf->tree[0]));
		if (hf->tree == NULL)
			return (ARCHIVE_FATAL);
	}
	hf->len_size = (int)len_size;
	hf->tbl_bits = tbl_bits;
	return (ARCHIVE_OK);
}