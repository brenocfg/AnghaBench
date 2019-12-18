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
struct object_id {int dummy; } ;
struct commit_list {TYPE_2__* item; struct commit_list* next; } ;
struct commit {int dummy; } ;
struct TYPE_3__ {struct object_id oid; } ;
struct TYPE_4__ {TYPE_1__ object; } ;

/* Variables and functions */
 char* _ (char*) ; 
 int /*<<< orphan*/  bisect_checkout (struct object_id const*,int) ; 
 int /*<<< orphan*/  current_bad_oid ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_commit_list (struct commit_list*) ; 
 struct commit_list* get_merge_bases_many (struct commit*,int,struct commit**) ; 
 int /*<<< orphan*/  good_revs ; 
 int /*<<< orphan*/  handle_bad_merge_base () ; 
 int /*<<< orphan*/  handle_skipped_merge_base (struct object_id const*) ; 
 scalar_t__ oid_array_lookup (int /*<<< orphan*/ *,struct object_id const*) ; 
 scalar_t__ oideq (struct object_id const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  skipped_revs ; 

__attribute__((used)) static void check_merge_bases(int rev_nr, struct commit **rev, int no_checkout)
{
	struct commit_list *result;

	result = get_merge_bases_many(rev[0], rev_nr - 1, rev + 1);

	for (; result; result = result->next) {
		const struct object_id *mb = &result->item->object.oid;
		if (oideq(mb, current_bad_oid)) {
			handle_bad_merge_base();
		} else if (0 <= oid_array_lookup(&good_revs, mb)) {
			continue;
		} else if (0 <= oid_array_lookup(&skipped_revs, mb)) {
			handle_skipped_merge_base(mb);
		} else {
			printf(_("Bisecting: a merge base must be tested\n"));
			exit(bisect_checkout(mb, no_checkout));
		}
	}

	free_commit_list(result);
}