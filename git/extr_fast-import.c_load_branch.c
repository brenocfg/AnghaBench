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
struct branch {int active; struct branch* active_next_branch; int /*<<< orphan*/  branch_tree; } ;

/* Variables and functions */
 struct branch* active_branches ; 
 int /*<<< orphan*/  branch_load_count ; 
 int /*<<< orphan*/  cur_active_branches ; 
 int /*<<< orphan*/  load_tree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void load_branch(struct branch *b)
{
	load_tree(&b->branch_tree);
	if (!b->active) {
		b->active = 1;
		b->active_next_branch = active_branches;
		active_branches = b;
		cur_active_branches++;
		branch_load_count++;
	}
}