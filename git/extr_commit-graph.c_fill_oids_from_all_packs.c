#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct write_commit_graph_context {scalar_t__ approx_nr_objects; scalar_t__ progress_done; int /*<<< orphan*/  progress; scalar_t__ report_progress; } ;

/* Variables and functions */
 int /*<<< orphan*/  FOR_EACH_OBJECT_PACK_ORDER ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  add_packed_commits ; 
 int /*<<< orphan*/  display_progress (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  for_each_packed_object (int /*<<< orphan*/ ,struct write_commit_graph_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_delayed_progress (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stop_progress (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fill_oids_from_all_packs(struct write_commit_graph_context *ctx)
{
	if (ctx->report_progress)
		ctx->progress = start_delayed_progress(
			_("Finding commits for commit graph among packed objects"),
			ctx->approx_nr_objects);
	for_each_packed_object(add_packed_commits, ctx,
			       FOR_EACH_OBJECT_PACK_ORDER);
	if (ctx->progress_done < ctx->approx_nr_objects)
		display_progress(ctx->progress, ctx->approx_nr_objects);
	stop_progress(&ctx->progress);
}