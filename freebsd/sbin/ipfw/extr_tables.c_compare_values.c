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
struct _table_value {scalar_t__ spare1; } ;

/* Variables and functions */

int
compare_values(const void *_a, const void *_b)
{
	struct _table_value *a, *b;

	a = (struct _table_value *)_a;
	b = (struct _table_value *)_b;

	if (a->spare1 < b->spare1)
		return (-1);
	else if (a->spare1 > b->spare1)
		return (1);

	return (0);
}