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
typedef  int uint32_t ;
struct TYPE_5__ {int nr; TYPE_3__** list; } ;
struct write_commit_graph_context {int /*<<< orphan*/  progress; scalar_t__ num_extra_edges; TYPE_2__ commits; scalar_t__ report_progress; } ;
struct TYPE_4__ {int /*<<< orphan*/  oid; } ;
struct TYPE_6__ {int /*<<< orphan*/  parents; TYPE_1__ object; } ;

/* Variables and functions */
 int /*<<< orphan*/  QSORT (TYPE_3__**,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  commit_compare ; 
 unsigned int commit_list_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  display_progress (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  oid_to_hex (int /*<<< orphan*/ *) ; 
 scalar_t__ oideq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  start_delayed_progress (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stop_progress (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sort_and_scan_merged_commits(struct write_commit_graph_context *ctx)
{
	uint32_t i;

	if (ctx->report_progress)
		ctx->progress = start_delayed_progress(
					_("Scanning merged commits"),
					ctx->commits.nr);

	QSORT(ctx->commits.list, ctx->commits.nr, commit_compare);

	ctx->num_extra_edges = 0;
	for (i = 0; i < ctx->commits.nr; i++) {
		display_progress(ctx->progress, i);

		if (i && oideq(&ctx->commits.list[i - 1]->object.oid,
			  &ctx->commits.list[i]->object.oid)) {
			die(_("unexpected duplicate commit id %s"),
			    oid_to_hex(&ctx->commits.list[i]->object.oid));
		} else {
			unsigned int num_parents;

			num_parents = commit_list_count(ctx->commits.list[i]->parents);
			if (num_parents > 2)
				ctx->num_extra_edges += num_parents - 1;
		}
	}

	stop_progress(&ctx->progress);
}