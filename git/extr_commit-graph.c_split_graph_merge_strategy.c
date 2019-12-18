#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_6__ {int nr; } ;
struct write_commit_graph_context {int num_commit_graphs_after; int num_commit_graphs_before; char* obj_dir; void** commit_graph_hash_after; TYPE_4__* r; int /*<<< orphan*/ * commit_graph_filenames_before; void** commit_graph_filenames_after; struct commit_graph* new_base_graph; TYPE_2__ commits; TYPE_1__* split_opts; } ;
struct commit_graph {int num_commits; struct commit_graph* base_graph; int /*<<< orphan*/  oid; int /*<<< orphan*/  obj_dir; int /*<<< orphan*/  filename; } ;
struct TYPE_8__ {TYPE_3__* objects; } ;
struct TYPE_7__ {struct commit_graph* commit_graph; } ;
struct TYPE_5__ {int max_commits; int size_multiple; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_ARRAY (void**,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* get_commit_graph_filename (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oid_to_hex (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 void* xstrdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void split_graph_merge_strategy(struct write_commit_graph_context *ctx)
{
	struct commit_graph *g;
	uint32_t num_commits;
	uint32_t i;

	int max_commits = 0;
	int size_mult = 2;

	if (ctx->split_opts) {
		max_commits = ctx->split_opts->max_commits;
		size_mult = ctx->split_opts->size_multiple;
	}

	g = ctx->r->objects->commit_graph;
	num_commits = ctx->commits.nr;
	ctx->num_commit_graphs_after = ctx->num_commit_graphs_before + 1;

	while (g && (g->num_commits <= size_mult * num_commits ||
		    (max_commits && num_commits > max_commits))) {
		if (strcmp(g->obj_dir, ctx->obj_dir))
			break;

		num_commits += g->num_commits;
		g = g->base_graph;

		ctx->num_commit_graphs_after--;
	}

	ctx->new_base_graph = g;

	if (ctx->num_commit_graphs_after == 2) {
		char *old_graph_name = get_commit_graph_filename(g->obj_dir);

		if (!strcmp(g->filename, old_graph_name) &&
		    strcmp(g->obj_dir, ctx->obj_dir)) {
			ctx->num_commit_graphs_after = 1;
			ctx->new_base_graph = NULL;
		}

		free(old_graph_name);
	}

	ALLOC_ARRAY(ctx->commit_graph_filenames_after, ctx->num_commit_graphs_after);
	ALLOC_ARRAY(ctx->commit_graph_hash_after, ctx->num_commit_graphs_after);

	for (i = 0; i < ctx->num_commit_graphs_after &&
		    i < ctx->num_commit_graphs_before; i++)
		ctx->commit_graph_filenames_after[i] = xstrdup(ctx->commit_graph_filenames_before[i]);

	i = ctx->num_commit_graphs_before - 1;
	g = ctx->r->objects->commit_graph;

	while (g) {
		if (i < ctx->num_commit_graphs_after)
			ctx->commit_graph_hash_after[i] = xstrdup(oid_to_hex(&g->oid));

		i--;
		g = g->base_graph;
	}
}