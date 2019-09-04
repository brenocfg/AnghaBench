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
typedef  int uint32_t ;
struct commit_graph {unsigned char* chunk_commit_data; int hash_len; } ;
struct commit {int graph_pos; int generation; } ;

/* Variables and functions */
 int GRAPH_DATA_WIDTH ; 
 int get_be32 (unsigned char const*) ; 

__attribute__((used)) static void fill_commit_graph_info(struct commit *item, struct commit_graph *g, uint32_t pos)
{
	const unsigned char *commit_data = g->chunk_commit_data + GRAPH_DATA_WIDTH * pos;
	item->graph_pos = pos;
	item->generation = get_be32(commit_data + g->hash_len + 8) >> 2;
}