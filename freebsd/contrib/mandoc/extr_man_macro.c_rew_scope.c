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
struct roff_node {scalar_t__ tok; scalar_t__ type; int flags; struct roff_node* parent; int /*<<< orphan*/ * child; } ;
struct roff_man {struct roff_node* last; } ;
typedef  enum roff_tok { ____Placeholder_roff_tok } roff_tok ;
struct TYPE_2__ {scalar_t__ fp; } ;

/* Variables and functions */
 scalar_t__ MAN_LP ; 
 scalar_t__ MAN_P ; 
 scalar_t__ MAN_PP ; 
 int MAN_RS ; 
 int MAN_SH ; 
 int MAN_SS ; 
 int NODE_VALID ; 
 scalar_t__ ROFFT_BLOCK ; 
 scalar_t__ ROFFT_ROOT ; 
 scalar_t__ blk_exp ; 
 TYPE_1__* man_macro (int) ; 
 int /*<<< orphan*/  man_unscope (struct roff_man*,struct roff_node*) ; 

__attribute__((used)) static void
rew_scope(struct roff_man *man, enum roff_tok tok)
{
	struct roff_node *n;

	/* Preserve empty paragraphs before RS. */

	n = man->last;
	if (tok == MAN_RS && n->child == NULL &&
	    (n->tok == MAN_P || n->tok == MAN_PP || n->tok == MAN_LP))
		return;

	for (;;) {
		if (n->type == ROFFT_ROOT)
			return;
		if (n->flags & NODE_VALID) {
			n = n->parent;
			continue;
		}
		if (n->type != ROFFT_BLOCK) {
			if (n->parent->type == ROFFT_ROOT) {
				man_unscope(man, n);
				return;
			} else {
				n = n->parent;
				continue;
			}
		}
		if (tok != MAN_SH && (n->tok == MAN_SH ||
		    (tok != MAN_SS && (n->tok == MAN_SS ||
		     man_macro(n->tok)->fp == blk_exp))))
			return;
		man_unscope(man, n);
		n = man->last;
	}
}