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
struct TYPE_3__ {int nr; int /*<<< orphan*/ * list; } ;
struct write_commit_graph_context {void* progress; TYPE_1__ oids; int /*<<< orphan*/  r; scalar_t__ report_progress; scalar_t__ split; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
struct commit {scalar_t__ graph_pos; TYPE_2__ object; } ;

/* Variables and functions */
 scalar_t__ COMMIT_NOT_FROM_GRAPH ; 
 int /*<<< orphan*/  REACHABLE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  add_missing_parents (struct write_commit_graph_context*,struct commit*) ; 
 int /*<<< orphan*/  display_progress (void*,int) ; 
 struct commit* lookup_commit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_commit (struct commit*) ; 
 int /*<<< orphan*/  parse_commit_no_graph (struct commit*) ; 
 void* start_delayed_progress (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stop_progress (void**) ; 

__attribute__((used)) static void close_reachable(struct write_commit_graph_context *ctx)
{
	int i;
	struct commit *commit;

	if (ctx->report_progress)
		ctx->progress = start_delayed_progress(
					_("Loading known commits in commit graph"),
					ctx->oids.nr);
	for (i = 0; i < ctx->oids.nr; i++) {
		display_progress(ctx->progress, i + 1);
		commit = lookup_commit(ctx->r, &ctx->oids.list[i]);
		if (commit)
			commit->object.flags |= REACHABLE;
	}
	stop_progress(&ctx->progress);

	/*
	 * As this loop runs, ctx->oids.nr may grow, but not more
	 * than the number of missing commits in the reachable
	 * closure.
	 */
	if (ctx->report_progress)
		ctx->progress = start_delayed_progress(
					_("Expanding reachable commits in commit graph"),
					0);
	for (i = 0; i < ctx->oids.nr; i++) {
		display_progress(ctx->progress, i + 1);
		commit = lookup_commit(ctx->r, &ctx->oids.list[i]);

		if (!commit)
			continue;
		if (ctx->split) {
			if (!parse_commit(commit) &&
			    commit->graph_pos == COMMIT_NOT_FROM_GRAPH)
				add_missing_parents(ctx, commit);
		} else if (!parse_commit_no_graph(commit))
			add_missing_parents(ctx, commit);
	}
	stop_progress(&ctx->progress);

	if (ctx->report_progress)
		ctx->progress = start_delayed_progress(
					_("Clearing commit marks in commit graph"),
					ctx->oids.nr);
	for (i = 0; i < ctx->oids.nr; i++) {
		display_progress(ctx->progress, i + 1);
		commit = lookup_commit(ctx->r, &ctx->oids.list[i]);

		if (commit)
			commit->object.flags &= ~REACHABLE;
	}
	stop_progress(&ctx->progress);
}