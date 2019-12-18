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
struct commit_list {TYPE_2__* item; struct commit_list* next; } ;
struct commit {struct commit_list* parents; } ;
struct TYPE_3__ {int flags; } ;
struct TYPE_4__ {TYPE_1__ object; } ;

/* Variables and functions */
 int SHOWN ; 
 int UNINTERESTING ; 

__attribute__((used)) static int has_unshown_parent(struct commit *commit)
{
	struct commit_list *parent;

	for (parent = commit->parents; parent; parent = parent->next)
		if (!(parent->item->object.flags & SHOWN) &&
		    !(parent->item->object.flags & UNINTERESTING))
			return 1;
	return 0;
}