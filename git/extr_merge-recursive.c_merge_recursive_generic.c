#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct object_id {int dummy; } ;
struct merge_options {char* ancestor; TYPE_1__* repo; int /*<<< orphan*/  branch2; int /*<<< orphan*/  branch1; } ;
struct lock_file {int dummy; } ;
struct commit_list {int dummy; } ;
struct commit {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int COMMIT_LOCK ; 
 int /*<<< orphan*/  LOCK_DIE_ON_ERROR ; 
 struct lock_file LOCK_INIT ; 
 int SKIP_IF_UNCHANGED ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  commit_list_insert (struct commit*,struct commit_list**) ; 
 int err (struct merge_options*,int /*<<< orphan*/ ,...) ; 
 struct commit* get_ref (TYPE_1__*,struct object_id const*,int /*<<< orphan*/ ) ; 
 int merge_recursive (struct merge_options*,struct commit*,struct commit*,struct commit_list*,struct commit**) ; 
 int /*<<< orphan*/  oid_to_hex (struct object_id const*) ; 
 int /*<<< orphan*/  repo_hold_locked_index (TYPE_1__*,struct lock_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rollback_lock_file (struct lock_file*) ; 
 scalar_t__ write_locked_index (int /*<<< orphan*/ ,struct lock_file*,int) ; 

int merge_recursive_generic(struct merge_options *opt,
			    const struct object_id *head,
			    const struct object_id *merge,
			    int num_merge_bases,
			    const struct object_id **merge_bases,
			    struct commit **result)
{
	int clean;
	struct lock_file lock = LOCK_INIT;
	struct commit *head_commit = get_ref(opt->repo, head, opt->branch1);
	struct commit *next_commit = get_ref(opt->repo, merge, opt->branch2);
	struct commit_list *ca = NULL;

	if (merge_bases) {
		int i;
		for (i = 0; i < num_merge_bases; ++i) {
			struct commit *base;
			if (!(base = get_ref(opt->repo, merge_bases[i],
					     oid_to_hex(merge_bases[i]))))
				return err(opt, _("Could not parse object '%s'"),
					   oid_to_hex(merge_bases[i]));
			commit_list_insert(base, &ca);
		}
		if (num_merge_bases == 1)
			opt->ancestor = "constructed merge base";
	}

	repo_hold_locked_index(opt->repo, &lock, LOCK_DIE_ON_ERROR);
	clean = merge_recursive(opt, head_commit, next_commit, ca,
				result);
	if (clean < 0) {
		rollback_lock_file(&lock);
		return clean;
	}

	if (write_locked_index(opt->repo->index, &lock,
			       COMMIT_LOCK | SKIP_IF_UNCHANGED))
		return err(opt, _("Unable to write index."));

	return clean ? 0 : 1;
}