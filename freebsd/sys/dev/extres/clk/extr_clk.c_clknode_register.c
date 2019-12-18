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
struct clknode {int flags; } ;
struct clkdom {int /*<<< orphan*/  clknode_list; } ;

/* Variables and functions */
 int CLKNODE_INIT (struct clknode*,int /*<<< orphan*/ ) ; 
 int CLK_NODE_REGISTERED ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct clknode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clkdom_link ; 
 int /*<<< orphan*/  clknode_get_device (struct clknode*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

struct clknode *
clknode_register(struct clkdom * clkdom, struct clknode *clknode)
{
	int rv;

	/* Skip already registered linked node */
	if (clknode->flags & CLK_NODE_REGISTERED)
		return(clknode);

	rv = CLKNODE_INIT(clknode, clknode_get_device(clknode));
	if (rv != 0) {
		printf(" CLKNODE_INIT failed: %d\n", rv);
		return (NULL);
	}

	TAILQ_INSERT_TAIL(&clkdom->clknode_list, clknode, clkdom_link);
	clknode->flags |= CLK_NODE_REGISTERED;
	return (clknode);
}