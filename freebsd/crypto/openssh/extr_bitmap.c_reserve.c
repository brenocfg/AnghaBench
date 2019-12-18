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
typedef  int u_int ;
struct bitmap {size_t top; size_t len; int /*<<< orphan*/ * d; } ;
typedef  int /*<<< orphan*/  BITMAP_WTYPE ;

/* Variables and functions */
 int BITMAP_BITS ; 
 int /*<<< orphan*/  BITMAP_BYTES ; 
 int BITMAP_MAX ; 
 int /*<<< orphan*/ * recallocarray (int /*<<< orphan*/ *,size_t,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
reserve(struct bitmap *b, u_int n)
{
	BITMAP_WTYPE *tmp;
	size_t nlen;

	if (b->top >= b->len || n > BITMAP_MAX)
		return -1; /* invalid */
	nlen = (n / BITMAP_BITS) + 1;
	if (b->len < nlen) {
		if ((tmp = recallocarray(b->d, b->len,
		    nlen, BITMAP_BYTES)) == NULL)
			return -1;
		b->d = tmp;
		b->len = nlen;
	}
	return 0;
}