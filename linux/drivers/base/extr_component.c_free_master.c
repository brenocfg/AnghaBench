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
struct master {int /*<<< orphan*/  node; struct component_match* match; } ;
struct component_match {int num; TYPE_1__* compare; } ;
struct component {int /*<<< orphan*/ * master; } ;
struct TYPE_2__ {struct component* component; } ;

/* Variables and functions */
 int /*<<< orphan*/  component_master_debugfs_del (struct master*) ; 
 int /*<<< orphan*/  kfree (struct master*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_master(struct master *master)
{
	struct component_match *match = master->match;
	int i;

	component_master_debugfs_del(master);
	list_del(&master->node);

	if (match) {
		for (i = 0; i < match->num; i++) {
			struct component *c = match->compare[i].component;
			if (c)
				c->master = NULL;
		}
	}

	kfree(master);
}