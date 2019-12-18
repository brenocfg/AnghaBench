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
struct roff_node {scalar_t__ type; int tok; struct roff_node* parent; } ;
struct roff_man {struct roff_node* last; } ;
typedef  enum roff_tok { ____Placeholder_roff_tok } roff_tok ;

/* Variables and functions */
 scalar_t__ ROFFT_ELEM ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  rew_last (struct roff_man*,struct roff_node*) ; 

__attribute__((used)) static void
rew_elem(struct roff_man *mdoc, enum roff_tok tok)
{
	struct roff_node *n;

	n = mdoc->last;
	if (n->type != ROFFT_ELEM)
		n = n->parent;
	assert(n->type == ROFFT_ELEM);
	assert(tok == n->tok);
	rew_last(mdoc, n);
}