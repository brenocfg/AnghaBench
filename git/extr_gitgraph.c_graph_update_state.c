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
struct git_graph {int prev_state; int state; } ;
typedef  enum graph_state { ____Placeholder_graph_state } graph_state ;

/* Variables and functions */

__attribute__((used)) static void graph_update_state(struct git_graph *graph, enum graph_state s)
{
	graph->prev_state = graph->state;
	graph->state = s;
}