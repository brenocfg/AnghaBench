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
struct rev_info {int max_age; int /*<<< orphan*/  track_linear; int /*<<< orphan*/  ignore_missing_links; int /*<<< orphan*/  commits; scalar_t__ topo_walk_info; scalar_t__ reflog_info; int /*<<< orphan*/  limited; } ;
struct TYPE_2__ {int flags; int /*<<< orphan*/  oid; } ;
struct commit {TYPE_1__ object; } ;

/* Variables and functions */
 int ADDED ; 
 int SEEN ; 
 int SHOWN ; 
#define  commit_error 129 
#define  commit_ignore 128 
 int comparison_date (struct rev_info*,struct commit*) ; 
 int /*<<< orphan*/  die (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expand_topo_walk (struct rev_info*,struct commit*) ; 
 struct commit* next_reflog_entry (scalar_t__) ; 
 struct commit* next_topo_commit (struct rev_info*) ; 
 int /*<<< orphan*/  oid_to_hex (int /*<<< orphan*/ *) ; 
 struct commit* pop_commit (int /*<<< orphan*/ *) ; 
 scalar_t__ process_parents (struct rev_info*,struct commit*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int simplify_commit (struct rev_info*,struct commit*) ; 
 int /*<<< orphan*/  track_linear (struct rev_info*,struct commit*) ; 
 int /*<<< orphan*/  try_to_simplify_commit (struct rev_info*,struct commit*) ; 

__attribute__((used)) static struct commit *get_revision_1(struct rev_info *revs)
{
	while (1) {
		struct commit *commit;

		if (revs->reflog_info)
			commit = next_reflog_entry(revs->reflog_info);
		else if (revs->topo_walk_info)
			commit = next_topo_commit(revs);
		else
			commit = pop_commit(&revs->commits);

		if (!commit)
			return NULL;

		if (revs->reflog_info)
			commit->object.flags &= ~(ADDED | SEEN | SHOWN);

		/*
		 * If we haven't done the list limiting, we need to look at
		 * the parents here. We also need to do the date-based limiting
		 * that we'd otherwise have done in limit_list().
		 */
		if (!revs->limited) {
			if (revs->max_age != -1 &&
			    comparison_date(revs, commit) < revs->max_age)
				continue;

			if (revs->reflog_info)
				try_to_simplify_commit(revs, commit);
			else if (revs->topo_walk_info)
				expand_topo_walk(revs, commit);
			else if (process_parents(revs, commit, &revs->commits, NULL) < 0) {
				if (!revs->ignore_missing_links)
					die("Failed to traverse parents of commit %s",
						oid_to_hex(&commit->object.oid));
			}
		}

		switch (simplify_commit(revs, commit)) {
		case commit_ignore:
			continue;
		case commit_error:
			die("Failed to simplify parents of commit %s",
			    oid_to_hex(&commit->object.oid));
		default:
			if (revs->track_linear)
				track_linear(revs, commit);
			return commit;
		}
	}
}