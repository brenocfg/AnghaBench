#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct object_id {int dummy; } ;
struct commit_list {TYPE_3__* item; scalar_t__ next; } ;
struct TYPE_4__ {struct object_id oid; } ;
struct commit {TYPE_1__ object; } ;
struct TYPE_5__ {struct object_id oid; } ;
struct TYPE_6__ {TYPE_2__ object; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_commit_list (struct commit_list*) ; 
 struct commit_list* get_merge_bases (struct commit*,struct commit*) ; 
 scalar_t__ is_linear_history (struct commit*,struct commit*) ; 
 struct commit* lookup_commit (int /*<<< orphan*/ ,struct object_id*) ; 
 struct object_id null_oid ; 
 int /*<<< orphan*/  oidcpy (struct object_id*,struct object_id*) ; 
 int /*<<< orphan*/  oideq (struct object_id*,struct object_id*) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static int can_fast_forward(struct commit *onto, struct commit *upstream,
			    struct commit *restrict_revision,
			    struct object_id *head_oid, struct object_id *merge_base)
{
	struct commit *head = lookup_commit(the_repository, head_oid);
	struct commit_list *merge_bases = NULL;
	int res = 0;

	if (!head)
		goto done;

	merge_bases = get_merge_bases(onto, head);
	if (!merge_bases || merge_bases->next) {
		oidcpy(merge_base, &null_oid);
		goto done;
	}

	oidcpy(merge_base, &merge_bases->item->object.oid);
	if (!oideq(merge_base, &onto->object.oid))
		goto done;

	if (restrict_revision && !oideq(&restrict_revision->object.oid, merge_base))
		goto done;

	if (!upstream)
		goto done;

	free_commit_list(merge_bases);
	merge_bases = get_merge_bases(upstream, head);
	if (!merge_bases || merge_bases->next)
		goto done;

	if (!oideq(&onto->object.oid, &merge_bases->item->object.oid))
		goto done;

	res = 1;

done:
	free_commit_list(merge_bases);
	return res && is_linear_history(onto, head);
}