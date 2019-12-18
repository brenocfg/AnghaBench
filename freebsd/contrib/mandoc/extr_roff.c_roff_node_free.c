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
struct roff_node {scalar_t__ type; struct roff_node* string; int /*<<< orphan*/  eqn; struct roff_node* norm; int /*<<< orphan*/ * args; } ;

/* Variables and functions */
 scalar_t__ ROFFT_BLOCK ; 
 scalar_t__ ROFFT_ELEM ; 
 int /*<<< orphan*/  eqn_box_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct roff_node*) ; 
 int /*<<< orphan*/  mdoc_argv_free (int /*<<< orphan*/ *) ; 

void
roff_node_free(struct roff_node *n)
{

	if (n->args != NULL)
		mdoc_argv_free(n->args);
	if (n->type == ROFFT_BLOCK || n->type == ROFFT_ELEM)
		free(n->norm);
	eqn_box_free(n->eqn);
	free(n->string);
	free(n);
}