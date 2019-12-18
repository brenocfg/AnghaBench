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
typedef  scalar_t__ u_char ;
struct bitmap {size_t top; size_t* d; } ;
typedef  size_t BITMAP_WTYPE ;

/* Variables and functions */
 int BITMAP_BITS ; 
 int BITMAP_BYTES ; 
 int BITMAP_MAX ; 
 int /*<<< orphan*/  bitmap_zero (struct bitmap*) ; 
 int reserve (struct bitmap*,size_t) ; 
 int /*<<< orphan*/  retop (struct bitmap*) ; 

int
bitmap_from_string(struct bitmap *b, const void *p, size_t l)
{
	int r;
	size_t i, offset, shift;
	const u_char *s = (const u_char *)p;

	if (l > BITMAP_MAX / 8)
		return -1;
	if ((r = reserve(b, l * 8)) != 0)
		return r;
	bitmap_zero(b);
	if (l == 0)
		return 0;
	b->top = offset = ((l + (BITMAP_BYTES - 1)) / BITMAP_BYTES) - 1;
	shift = ((l + (BITMAP_BYTES - 1)) % BITMAP_BYTES) * 8;
	for (i = 0; i < l; i++) {
		b->d[offset] |= (BITMAP_WTYPE)s[i] << shift;
		if (shift == 0) {
			offset--;
			shift = BITMAP_BITS - 8;
		} else
			shift -= 8;
	}
	retop(b);
	return 0;
}