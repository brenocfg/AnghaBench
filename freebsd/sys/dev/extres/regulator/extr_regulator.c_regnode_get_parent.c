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
struct regnode {struct regnode* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_TOPO_ASSERT () ; 
 int regnode_resolve_parent (struct regnode*) ; 

struct regnode *
regnode_get_parent(struct regnode *regnode)
{
	int rv;

	REG_TOPO_ASSERT();

	rv = regnode_resolve_parent(regnode);
	if (rv != 0)
		return (NULL);

	return (regnode->parent);
}