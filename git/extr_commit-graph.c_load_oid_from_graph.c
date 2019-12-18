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
typedef  scalar_t__ uint32_t ;
struct object_id {int /*<<< orphan*/  hash; } ;
struct commit_graph {scalar_t__ num_commits_in_base; scalar_t__ num_commits; scalar_t__ hash_len; scalar_t__ chunk_oid_lookup; struct commit_graph* base_graph; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashcpy (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void load_oid_from_graph(struct commit_graph *g,
				uint32_t pos,
				struct object_id *oid)
{
	uint32_t lex_index;

	while (g && pos < g->num_commits_in_base)
		g = g->base_graph;

	if (!g)
		BUG("NULL commit-graph");

	if (pos >= g->num_commits + g->num_commits_in_base)
		die(_("invalid commit position. commit-graph is likely corrupt"));

	lex_index = pos - g->num_commits_in_base;

	hashcpy(oid->hash, g->chunk_oid_lookup + g->hash_len * lex_index);
}