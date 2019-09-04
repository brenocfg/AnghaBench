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
struct branch {struct branch* table_next_branch; } ;

/* Variables and functions */
 struct branch** branch_table ; 
 unsigned int branch_table_sz ; 
 int /*<<< orphan*/  failure ; 
 int /*<<< orphan*/  update_branch (struct branch*) ; 

__attribute__((used)) static void dump_branches(void)
{
	unsigned int i;
	struct branch *b;

	for (i = 0; i < branch_table_sz; i++) {
		for (b = branch_table[i]; b; b = b->table_next_branch)
			failure |= update_branch(b);
	}
}