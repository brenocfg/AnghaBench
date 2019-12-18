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
struct blame_line_tracker {scalar_t__ is_parent; scalar_t__ s_lno; } ;

/* Variables and functions */

__attribute__((used)) static int are_lines_adjacent(struct blame_line_tracker *first,
			      struct blame_line_tracker *second)
{
	return first->is_parent == second->is_parent &&
	       first->s_lno + 1 == second->s_lno;
}