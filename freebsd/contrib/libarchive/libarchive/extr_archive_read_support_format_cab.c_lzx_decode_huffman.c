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
struct huffman {int* tbl; int len_size; } ;

/* Variables and functions */

__attribute__((used)) static inline int
lzx_decode_huffman(struct huffman *hf, unsigned rbits)
{
	int c;
	c = hf->tbl[rbits];
	if (c < hf->len_size)
		return (c);
	return (0);
}