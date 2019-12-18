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
typedef  int uint32_t ;
struct TYPE_2__ {int nr; int /*<<< orphan*/ * list; } ;
struct write_commit_graph_context {int /*<<< orphan*/  progress; TYPE_1__ oids; int /*<<< orphan*/  r; scalar_t__ split; scalar_t__ report_progress; } ;
struct commit {scalar_t__ graph_pos; } ;

/* Variables and functions */
 scalar_t__ COMMIT_NOT_FROM_GRAPH ; 
 int /*<<< orphan*/  QSORT (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  display_progress (int /*<<< orphan*/ ,int) ; 
 struct commit* lookup_commit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oid_compare ; 
 int /*<<< orphan*/  oideq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  start_delayed_progress (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stop_progress (int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint32_t count_distinct_commits(struct write_commit_graph_context *ctx)
{
	uint32_t i, count_distinct = 1;

	if (ctx->report_progress)
		ctx->progress = start_delayed_progress(
			_("Counting distinct commits in commit graph"),
			ctx->oids.nr);
	display_progress(ctx->progress, 0); /* TODO: Measure QSORT() progress */
	QSORT(ctx->oids.list, ctx->oids.nr, oid_compare);

	for (i = 1; i < ctx->oids.nr; i++) {
		display_progress(ctx->progress, i + 1);
		if (!oideq(&ctx->oids.list[i - 1], &ctx->oids.list[i])) {
			if (ctx->split) {
				struct commit *c = lookup_commit(ctx->r, &ctx->oids.list[i]);

				if (!c || c->graph_pos != COMMIT_NOT_FROM_GRAPH)
					continue;
			}

			count_distinct++;
		}
	}
	stop_progress(&ctx->progress);

	return count_distinct;
}