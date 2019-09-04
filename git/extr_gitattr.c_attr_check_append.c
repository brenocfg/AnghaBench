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
struct git_attr {int dummy; } ;
struct attr_check_item {struct git_attr const* attr; } ;
struct attr_check {scalar_t__ nr; struct attr_check_item* items; int /*<<< orphan*/  alloc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (struct attr_check_item*,scalar_t__,int /*<<< orphan*/ ) ; 

struct attr_check_item *attr_check_append(struct attr_check *check,
					  const struct git_attr *attr)
{
	struct attr_check_item *item;

	ALLOC_GROW(check->items, check->nr + 1, check->alloc);
	item = &check->items[check->nr++];
	item->attr = attr;
	return item;
}