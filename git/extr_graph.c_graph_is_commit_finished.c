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
struct git_graph {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ GRAPH_PADDING ; 

int graph_is_commit_finished(struct git_graph const *graph)
{
	return (graph->state == GRAPH_PADDING);
}