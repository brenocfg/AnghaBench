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
struct commit_list {struct commit_list* next; struct commit* item; } ;
struct TYPE_2__ {unsigned int flags; } ;
struct commit {TYPE_1__ object; } ;

/* Variables and functions */
 unsigned int TREESAME ; 
 unsigned int UNINTERESTING ; 

__attribute__((used)) static int estimate_commit_count(struct commit_list *list)
{
	int n = 0;

	while (list) {
		struct commit *commit = list->item;
		unsigned int flags = commit->object.flags;
		list = list->next;
		if (!(flags & (TREESAME | UNINTERESTING)))
			n++;
	}
	return n;
}