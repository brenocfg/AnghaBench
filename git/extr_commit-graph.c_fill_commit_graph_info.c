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
struct commit_graph {scalar_t__ num_commits_in_base; unsigned char* chunk_commit_data; int hash_len; struct commit_graph* base_graph; } ;
struct commit {int generation; scalar_t__ graph_pos; } ;

/* Variables and functions */
 scalar_t__ GRAPH_DATA_WIDTH ; 
 int get_be32 (unsigned char const*) ; 

__attribute__((used)) static void fill_commit_graph_info(struct commit *item, struct commit_graph *g, uint32_t pos)
{
	const unsigned char *commit_data;
	uint32_t lex_index;

	while (pos < g->num_commits_in_base)
		g = g->base_graph;

	lex_index = pos - g->num_commits_in_base;
	commit_data = g->chunk_commit_data + GRAPH_DATA_WIDTH * lex_index;
	item->graph_pos = pos;
	item->generation = get_be32(commit_data + g->hash_len + 8) >> 2;
}