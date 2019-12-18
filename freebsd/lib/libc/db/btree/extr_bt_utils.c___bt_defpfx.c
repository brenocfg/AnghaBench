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

size_t
__bt_defpfx(const DBT *a, const DBT *b)
{
	u_char *p1, *p2;
	size_t cnt, len;

	cnt = 1;
	len = MIN(a->size, b->size);
	for (p1 = a->data, p2 = b->data; len--; ++p1, ++p2, ++cnt)
		if (*p1 != *p2)
			return (cnt);

	/* a->size must be <= b->size, or they wouldn't be in this order. */
	return (a->size < b->size ? a->size + 1 : a->size);
}