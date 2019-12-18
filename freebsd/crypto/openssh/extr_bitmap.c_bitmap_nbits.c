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
struct bitmap {scalar_t__ top; scalar_t__ len; scalar_t__* d; } ;
typedef  int BITMAP_WTYPE ;

/* Variables and functions */
 int BITMAP_BITS ; 
 int /*<<< orphan*/  retop (struct bitmap*) ; 

size_t
bitmap_nbits(struct bitmap *b)
{
	size_t bits;
	BITMAP_WTYPE w;

	retop(b);
	if (b->top >= b->len)
		return 0; /* invalid */
	if (b->len == 0 || (b->top == 0 && b->d[0] == 0))
		return 0;
	/* Find MSB set */
	w = b->d[b->top];
	bits = (b->top + 1) * BITMAP_BITS;
	while (!(w & ((BITMAP_WTYPE)1 << (BITMAP_BITS - 1)))) {
		w <<= 1;
		bits--;
	}
	return bits;
}