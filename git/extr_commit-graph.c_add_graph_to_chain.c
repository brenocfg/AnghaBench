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
struct object_id {int /*<<< orphan*/  hash; } ;
struct commit_graph {int hash_len; scalar_t__ num_commits_in_base; scalar_t__ num_commits; struct commit_graph* base_graph; scalar_t__ chunk_base_graphs; int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  hasheq (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  oideq (struct object_id*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int add_graph_to_chain(struct commit_graph *g,
			      struct commit_graph *chain,
			      struct object_id *oids,
			      int n)
{
	struct commit_graph *cur_g = chain;

	if (n && !g->chunk_base_graphs) {
		warning(_("commit-graph has no base graphs chunk"));
		return 0;
	}

	while (n) {
		n--;

		if (!cur_g ||
		    !oideq(&oids[n], &cur_g->oid) ||
		    !hasheq(oids[n].hash, g->chunk_base_graphs + g->hash_len * n)) {
			warning(_("commit-graph chain does not match"));
			return 0;
		}

		cur_g = cur_g->base_graph;
	}

	g->base_graph = chain;

	if (chain)
		g->num_commits_in_base = chain->num_commits + chain->num_commits_in_base;

	return 1;
}