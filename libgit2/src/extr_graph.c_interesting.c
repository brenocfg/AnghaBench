#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_pqueue ;
struct TYPE_7__ {int flags; } ;
typedef  TYPE_2__ git_commit_list_node ;
struct TYPE_8__ {struct TYPE_8__* next; TYPE_1__* item; } ;
typedef  TYPE_3__ git_commit_list ;
struct TYPE_6__ {int flags; } ;

/* Variables and functions */
 int STALE ; 
 TYPE_2__* git_pqueue_get (int /*<<< orphan*/ *,unsigned int) ; 
 unsigned int git_pqueue_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int interesting(git_pqueue *list, git_commit_list *roots)
{
	unsigned int i;

	for (i = 0; i < git_pqueue_size(list); i++) {
		git_commit_list_node *commit = git_pqueue_get(list, i);
		if ((commit->flags & STALE) == 0)
			return 1;
	}

	while(roots) {
		if ((roots->item->flags & STALE) == 0)
			return 1;
		roots = roots->next;
	}

	return 0;
}