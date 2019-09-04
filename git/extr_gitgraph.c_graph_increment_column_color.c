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
struct git_graph {int default_column_color; } ;

/* Variables and functions */
 int column_colors_max ; 

__attribute__((used)) static void graph_increment_column_color(struct git_graph *graph)
{
	graph->default_column_color = (graph->default_column_color + 1) %
		column_colors_max;
}