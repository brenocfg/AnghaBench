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
struct addrtree {int /*<<< orphan*/  env; int /*<<< orphan*/  (* delfunc ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;scalar_t__ (* sizefunc ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  size_bytes; } ;
struct addrnode {int /*<<< orphan*/ * elem; } ;

/* Variables and functions */
 scalar_t__ stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
clean_node(struct addrtree *tree, struct addrnode *node)
{
	if (!node->elem) return;
	tree->size_bytes -= tree->sizefunc(node->elem);
	tree->delfunc(tree->env, node->elem);
	node->elem = NULL;
}