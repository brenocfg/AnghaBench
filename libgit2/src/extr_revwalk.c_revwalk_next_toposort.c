#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  iterator_topo; } ;
typedef  TYPE_1__ git_revwalk ;
struct TYPE_8__ {int /*<<< orphan*/  uninteresting; } ;
typedef  TYPE_2__ git_commit_list_node ;

/* Variables and functions */
 int get_revision (TYPE_2__**,TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int revwalk_next_toposort(git_commit_list_node **object_out, git_revwalk *walk)
{
	int error;
	git_commit_list_node *next;

	while (!(error = get_revision(&next, walk, &walk->iterator_topo))) {
		/* Some commits might become uninteresting after being added to the list */
		if (!next->uninteresting) {
			*object_out = next;
			return 0;
		}
	}

	return error;
}