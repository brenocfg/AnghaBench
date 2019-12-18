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
struct eqn_node {struct eqn_def* defs; int /*<<< orphan*/  toksz; int /*<<< orphan*/  start; scalar_t__ defsz; } ;
struct eqn_def {scalar_t__ keysz; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 scalar_t__ STRNEQ (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct eqn_def *
eqn_def_find(struct eqn_node *ep)
{
	int		 i;

	for (i = 0; i < (int)ep->defsz; i++)
		if (ep->defs[i].keysz && STRNEQ(ep->defs[i].key,
		    ep->defs[i].keysz, ep->start, ep->toksz))
			return &ep->defs[i];

	return NULL;
}