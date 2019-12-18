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
struct tree_islands_todo {int depth; } ;

/* Variables and functions */

__attribute__((used)) static int tree_depth_compare(const void *a, const void *b)
{
	const struct tree_islands_todo *todo_a = a;
	const struct tree_islands_todo *todo_b = b;

	return todo_a->depth - todo_b->depth;
}