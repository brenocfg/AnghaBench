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
struct eqn_node {struct eqn_node* defs; struct eqn_node* data; struct eqn_node* val; struct eqn_node* key; scalar_t__ defsz; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct eqn_node*) ; 

void
eqn_free(struct eqn_node *p)
{
	int		 i;

	if (p == NULL)
		return;

	for (i = 0; i < (int)p->defsz; i++) {
		free(p->defs[i].key);
		free(p->defs[i].val);
	}

	free(p->data);
	free(p->defs);
	free(p);
}