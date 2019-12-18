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
struct attr_check {int /*<<< orphan*/  stack; scalar_t__ all_attrs_nr; int /*<<< orphan*/  all_attrs; scalar_t__ nr; scalar_t__ alloc; int /*<<< orphan*/  items; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_AND_NULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drop_attr_stack (int /*<<< orphan*/ *) ; 

void attr_check_clear(struct attr_check *check)
{
	FREE_AND_NULL(check->items);
	check->alloc = 0;
	check->nr = 0;

	FREE_AND_NULL(check->all_attrs);
	check->all_attrs_nr = 0;

	drop_attr_stack(&check->stack);
}