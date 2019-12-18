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
struct tree {int dummy; } ;
struct repository {int dummy; } ;
struct object_id {int /*<<< orphan*/  hash; } ;
struct commit_graph {scalar_t__ num_commits_in_base; unsigned char* chunk_commit_data; struct commit_graph* base_graph; } ;
struct commit {scalar_t__ graph_pos; struct tree* maybe_tree; } ;

/* Variables and functions */
 int GRAPH_DATA_WIDTH ; 
 int /*<<< orphan*/  hashcpy (int /*<<< orphan*/ ,unsigned char const*) ; 
 int /*<<< orphan*/  lookup_tree (struct repository*,struct object_id*) ; 
 int /*<<< orphan*/  set_commit_tree (struct commit*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct tree *load_tree_for_commit(struct repository *r,
					 struct commit_graph *g,
					 struct commit *c)
{
	struct object_id oid;
	const unsigned char *commit_data;

	while (c->graph_pos < g->num_commits_in_base)
		g = g->base_graph;

	commit_data = g->chunk_commit_data +
			GRAPH_DATA_WIDTH * (c->graph_pos - g->num_commits_in_base);

	hashcpy(oid.hash, commit_data);
	set_commit_tree(c, lookup_tree(r, &oid));

	return c->maybe_tree;
}