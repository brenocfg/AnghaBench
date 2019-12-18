#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct klist_iter {int dummy; } ;
struct device {TYPE_1__* p; } ;
struct TYPE_2__ {int /*<<< orphan*/  klist_children; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_name (struct device*) ; 
 scalar_t__ get_device (struct device*) ; 
 int /*<<< orphan*/  klist_iter_exit (struct klist_iter*) ; 
 int /*<<< orphan*/  klist_iter_init (int /*<<< orphan*/ *,struct klist_iter*) ; 
 struct device* next_device (struct klist_iter*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

struct device *device_find_child_by_name(struct device *parent,
					 const char *name)
{
	struct klist_iter i;
	struct device *child;

	if (!parent)
		return NULL;

	klist_iter_init(&parent->p->klist_children, &i);
	while ((child = next_device(&i)))
		if (!strcmp(dev_name(child), name) && get_device(child))
			break;
	klist_iter_exit(&i);
	return child;
}