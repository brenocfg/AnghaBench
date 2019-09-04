#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* attr; } ;
struct match_attr {TYPE_2__ u; scalar_t__ is_macro; } ;
struct attr_stack {int num_matches; struct match_attr** attrs; struct attr_stack* prev; } ;
struct all_attrs_item {struct match_attr const* macro; } ;
struct TYPE_3__ {int attr_nr; } ;

/* Variables and functions */

__attribute__((used)) static void determine_macros(struct all_attrs_item *all_attrs,
			     const struct attr_stack *stack)
{
	for (; stack; stack = stack->prev) {
		int i;
		for (i = stack->num_matches - 1; i >= 0; i--) {
			const struct match_attr *ma = stack->attrs[i];
			if (ma->is_macro) {
				int n = ma->u.attr->attr_nr;
				if (!all_attrs[n].macro) {
					all_attrs[n].macro = ma;
				}
			}
		}
	}
}