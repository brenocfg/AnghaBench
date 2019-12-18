#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct eqn_node {TYPE_1__* node; } ;
struct eqn_def {scalar_t__ valsz; scalar_t__ keysz; int /*<<< orphan*/ * val; int /*<<< orphan*/ * key; } ;
struct TYPE_2__ {int /*<<< orphan*/  pos; int /*<<< orphan*/  line; } ;

/* Variables and functions */
 scalar_t__ EQN_TOK_EOF ; 
 int /*<<< orphan*/  MANDOCERR_REQ_EMPTY ; 
 int /*<<< orphan*/  MODE_NOSUB ; 
 struct eqn_def* eqn_def_find (struct eqn_node*) ; 
 scalar_t__ eqn_next (struct eqn_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mandoc_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
eqn_undef(struct eqn_node *ep)
{
	struct eqn_def	*def;

	if (eqn_next(ep, MODE_NOSUB) == EQN_TOK_EOF) {
		mandoc_msg(MANDOCERR_REQ_EMPTY,
		    ep->node->line, ep->node->pos, "undef");
		return;
	}
	if ((def = eqn_def_find(ep)) == NULL)
		return;
	free(def->key);
	free(def->val);
	def->key = def->val = NULL;
	def->keysz = def->valsz = 0;
}