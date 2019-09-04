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
struct strbuf {int dummy; } ;
struct git_graph {int width; } ;

/* Variables and functions */
 int /*<<< orphan*/  strbuf_addchars (struct strbuf*,char,int) ; 

__attribute__((used)) static void graph_pad_horizontally(struct git_graph *graph, struct strbuf *sb,
				   int chars_written)
{
	/*
	 * Add additional spaces to the end of the strbuf, so that all
	 * lines for a particular commit have the same width.
	 *
	 * This way, fields printed to the right of the graph will remain
	 * aligned for the entire commit.
	 */
	if (chars_written < graph->width)
		strbuf_addchars(sb, ' ', graph->width - chars_written);
}