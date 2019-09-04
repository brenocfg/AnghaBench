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
struct branch {int /*<<< orphan*/  name; struct branch* table_next_branch; } ;

/* Variables and functions */
 struct branch** branch_table ; 
 unsigned int branch_table_sz ; 
 unsigned int hc_str (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static struct branch *lookup_branch(const char *name)
{
	unsigned int hc = hc_str(name, strlen(name)) % branch_table_sz;
	struct branch *b;

	for (b = branch_table[hc]; b; b = b->table_next_branch)
		if (!strcmp(name, b->name))
			return b;
	return NULL;
}