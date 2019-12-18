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
struct huffman {int len_size; int tbl_bits; int /*<<< orphan*/ * tbl; int /*<<< orphan*/ * bitlen; } ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/ * calloc (size_t,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (size_t) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int
lzx_huffman_init(struct huffman *hf, size_t len_size, int tbl_bits)
{

	if (hf->bitlen == NULL || hf->len_size != (int)len_size) {
		free(hf->bitlen);
		hf->bitlen = calloc(len_size,  sizeof(hf->bitlen[0]));
		if (hf->bitlen == NULL)
			return (ARCHIVE_FATAL);
		hf->len_size = (int)len_size;
	} else
		memset(hf->bitlen, 0, len_size *  sizeof(hf->bitlen[0]));
	if (hf->tbl == NULL) {
		hf->tbl = malloc(((size_t)1 << tbl_bits) * sizeof(hf->tbl[0]));
		if (hf->tbl == NULL)
			return (ARCHIVE_FATAL);
		hf->tbl_bits = tbl_bits;
	}
	return (ARCHIVE_OK);
}