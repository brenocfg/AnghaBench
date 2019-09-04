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
struct negotiation_state {int /*<<< orphan*/  non_common_revs; int /*<<< orphan*/  rev_list; } ;
struct TYPE_2__ {int flags; } ;
struct commit {TYPE_1__ object; } ;

/* Variables and functions */
 int COMMON ; 
 scalar_t__ parse_commit (struct commit*) ; 
 int /*<<< orphan*/  prio_queue_put (int /*<<< orphan*/ *,struct commit*) ; 

__attribute__((used)) static void rev_list_push(struct negotiation_state *ns,
			  struct commit *commit, int mark)
{
	if (!(commit->object.flags & mark)) {
		commit->object.flags |= mark;

		if (parse_commit(commit))
			return;

		prio_queue_put(&ns->rev_list, commit);

		if (!(commit->object.flags & COMMON))
			ns->non_common_revs++;
	}
}