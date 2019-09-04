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
struct commit_list {TYPE_1__* item; int /*<<< orphan*/  next; } ;
struct TYPE_5__ {int /*<<< orphan*/  oid; } ;
struct commit {TYPE_2__ object; } ;
struct TYPE_6__ {int /*<<< orphan*/  oid; } ;
struct TYPE_4__ {TYPE_3__ object; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_commit_list (struct commit_list*) ; 
 struct commit_list* get_merge_bases (struct commit*,struct commit*) ; 
 scalar_t__ is_linear_history (struct commit*,struct commit*) ; 
 struct commit* lookup_commit (int /*<<< orphan*/ ,struct object_id*) ; 
 int /*<<< orphan*/  null_oid ; 
 int /*<<< orphan*/  oidcpy (struct object_id*,int /*<<< orphan*/ *) ; 
 int oideq (struct object_id*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static int can_fast_forward(struct commit *onto, struct object_id *head_oid,
			    struct object_id *merge_base)
{
	struct commit *head = lookup_commit(the_repository, head_oid);
	struct commit_list *merge_bases;
	int res;

	if (!head)
		return 0;

	merge_bases = get_merge_bases(onto, head);
	if (merge_bases && !merge_bases->next) {
		oidcpy(merge_base, &merge_bases->item->object.oid);
		res = oideq(merge_base, &onto->object.oid);
	} else {
		oidcpy(merge_base, &null_oid);
		res = 0;
	}
	free_commit_list(merge_bases);
	return res && is_linear_history(onto, head);
}