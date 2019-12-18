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
struct roff_node {int flags; scalar_t__ type; size_t tok; struct roff_node* parent; } ;
struct roff_man {struct roff_node* last; } ;
typedef  enum roff_tok { ____Placeholder_roff_tok } roff_tok ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MANDOCERR_BLK_NEST ; 
 int MDOC_EXPLICIT ; 
 int NODE_ENDED ; 
 int NODE_VALID ; 
 scalar_t__ ROFFT_BLOCK ; 
 scalar_t__ ROFFT_HEAD ; 
 int /*<<< orphan*/  break_intermediate (struct roff_node*,struct roff_node*) ; 
 int /*<<< orphan*/  mandoc_msg (int /*<<< orphan*/ ,int,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdoc_endbody_alloc (struct roff_man*,int,int,int,struct roff_node*) ; 
 TYPE_1__* mdoc_macro (size_t) ; 
 int /*<<< orphan*/ * roff_name ; 

__attribute__((used)) static int
find_pending(struct roff_man *mdoc, enum roff_tok tok, int line, int ppos,
	struct roff_node *target)
{
	struct roff_node	*n;
	int			 irc;

	if (target->flags & NODE_VALID)
		return 0;

	irc = 0;
	for (n = mdoc->last; n != NULL && n != target; n = n->parent) {
		if (n->flags & NODE_ENDED)
			continue;
		if (n->type == ROFFT_BLOCK &&
		    mdoc_macro(n->tok)->flags & MDOC_EXPLICIT) {
			irc = 1;
			break_intermediate(mdoc->last, target);
			if (target->type == ROFFT_HEAD)
				target->flags |= NODE_ENDED;
			else if ( ! (target->flags & NODE_ENDED)) {
				mandoc_msg(MANDOCERR_BLK_NEST,
				    line, ppos, "%s breaks %s",
				    roff_name[tok], roff_name[n->tok]);
				mdoc_endbody_alloc(mdoc, line, ppos,
				    tok, target);
			}
		}
	}
	return irc;
}