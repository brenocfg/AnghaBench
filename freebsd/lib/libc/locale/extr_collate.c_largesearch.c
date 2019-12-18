#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int wchar_t ;
struct xlocale_collate {TYPE_2__* large_pri_table; TYPE_1__* info; } ;
struct TYPE_5__ {int const val; } ;
typedef  TYPE_2__ collate_large_t ;
struct TYPE_4__ {int large_count; } ;

/* Variables and functions */

__attribute__((used)) static collate_large_t *
largesearch(struct xlocale_collate *table, const wchar_t key)
{
	int low = 0;
	int high = table->info->large_count - 1;
	int next, compar;
	collate_large_t *p;
	collate_large_t *tab = table->large_pri_table;

	if (high < 0)
		return (NULL);

	while (low <= high) {
		next = (low + high) / 2;
		p = tab + next;
		compar = key - p->val;
		if (compar == 0)
			return (p);
		if (compar > 0)
			low = next + 1;
		else
			high = next - 1;
	}
	return (NULL);
}