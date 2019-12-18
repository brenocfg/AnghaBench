#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_char ;
struct TYPE_4__ {scalar_t__ size; scalar_t__* data; } ;
typedef  TYPE_1__ DBT ;

/* Variables and functions */
 size_t MIN (scalar_t__,scalar_t__) ; 

int
__bt_defcmp(const DBT *a, const DBT *b)
{
	size_t len;
	u_char *p1, *p2;

	/*
	 * XXX
	 * If a size_t doesn't fit in an int, this routine can lose.
	 * What we need is an integral type which is guaranteed to be
	 * larger than a size_t, and there is no such thing.
	 */
	len = MIN(a->size, b->size);
	for (p1 = a->data, p2 = b->data; len--; ++p1, ++p2)
		if (*p1 != *p2)
			return ((int)*p1 - (int)*p2);
	return ((int)a->size - (int)b->size);
}