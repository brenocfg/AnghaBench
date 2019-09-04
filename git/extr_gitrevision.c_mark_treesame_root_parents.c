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
struct commit_list {struct commit* item; struct commit_list* next; } ;
struct TYPE_2__ {int flags; } ;
struct commit {TYPE_1__ object; struct commit_list* parents; } ;

/* Variables and functions */
 int TMP_MARK ; 
 int TREESAME ; 

__attribute__((used)) static int mark_treesame_root_parents(struct commit *commit)
{
	struct commit_list *p;
	int marked = 0;

	for (p = commit->parents; p; p = p->next) {
		struct commit *parent = p->item;
		if (!parent->parents && (parent->object.flags & TREESAME)) {
			parent->object.flags |= TMP_MARK;
			marked++;
		}
	}

	return marked;
}