#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct git_graph {unsigned short default_column_color; TYPE_2__* revs; } ;
struct TYPE_3__ {int /*<<< orphan*/  use_color; } ;
struct TYPE_4__ {TYPE_1__ diffopt; } ;

/* Variables and functions */
 unsigned short column_colors_max ; 
 int /*<<< orphan*/  want_color (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned short graph_get_current_column_color(const struct git_graph *graph)
{
	if (!want_color(graph->revs->diffopt.use_color))
		return column_colors_max;
	return graph->default_column_color;
}