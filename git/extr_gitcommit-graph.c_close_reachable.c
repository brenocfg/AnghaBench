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
struct progress {int dummy; } ;
struct packed_oid_list {int nr; int /*<<< orphan*/ * list; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;
struct commit {TYPE_1__ object; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNINTERESTING ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  add_missing_parents (struct packed_oid_list*,struct commit*) ; 
 int /*<<< orphan*/  display_progress (struct progress*,int) ; 
 struct commit* lookup_commit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_commit_no_graph (struct commit*) ; 
 struct progress* start_delayed_progress (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stop_progress (struct progress**) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static void close_reachable(struct packed_oid_list *oids, int report_progress)
{
	int i;
	struct commit *commit;
	struct progress *progress = NULL;

	if (report_progress)
		progress = start_delayed_progress(
			_("Loading known commits in commit graph"), oids->nr);
	for (i = 0; i < oids->nr; i++) {
		display_progress(progress, i + 1);
		commit = lookup_commit(the_repository, &oids->list[i]);
		if (commit)
			commit->object.flags |= UNINTERESTING;
	}
	stop_progress(&progress);

	/*
	 * As this loop runs, oids->nr may grow, but not more
	 * than the number of missing commits in the reachable
	 * closure.
	 */
	if (report_progress)
		progress = start_delayed_progress(
			_("Expanding reachable commits in commit graph"), oids->nr);
	for (i = 0; i < oids->nr; i++) {
		display_progress(progress, i + 1);
		commit = lookup_commit(the_repository, &oids->list[i]);

		if (commit && !parse_commit_no_graph(commit))
			add_missing_parents(oids, commit);
	}
	stop_progress(&progress);

	if (report_progress)
		progress = start_delayed_progress(
			_("Clearing commit marks in commit graph"), oids->nr);
	for (i = 0; i < oids->nr; i++) {
		display_progress(progress, i + 1);
		commit = lookup_commit(the_repository, &oids->list[i]);

		if (commit)
			commit->object.flags &= ~UNINTERESTING;
	}
	stop_progress(&progress);
}