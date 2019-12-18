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
typedef  struct roff_node {int type; int flags; struct roff_node const* parent; int /*<<< orphan*/  tok; int /*<<< orphan*/  pos; int /*<<< orphan*/  line; } const roff_node ;
struct roff_man {struct roff_node const* last; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDOC_Ss ; 
 int NODE_BROKEN ; 
 int NODE_ENDED ; 
#define  ROFFT_BLOCK 129 
#define  ROFFT_HEAD 128 
 int /*<<< orphan*/  ROFF_NONOFILL ; 
 int /*<<< orphan*/  rew_last (struct roff_man*,struct roff_node const*) ; 
 int /*<<< orphan*/  roff_body_alloc (struct roff_man*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
rew_pending(struct roff_man *mdoc, const struct roff_node *n)
{

	for (;;) {
		rew_last(mdoc, n);

		if (mdoc->last == n) {
			switch (n->type) {
			case ROFFT_HEAD:
				roff_body_alloc(mdoc, n->line, n->pos,
				    n->tok);
				if (n->tok == MDOC_Ss)
					mdoc->flags &= ~ROFF_NONOFILL;
				break;
			case ROFFT_BLOCK:
				break;
			default:
				return;
			}
			if ( ! (n->flags & NODE_BROKEN))
				return;
		} else
			n = mdoc->last;

		for (;;) {
			if ((n = n->parent) == NULL)
				return;

			if (n->type == ROFFT_BLOCK ||
			    n->type == ROFFT_HEAD) {
				if (n->flags & NODE_ENDED)
					break;
				else
					return;
			}
		}
	}
}