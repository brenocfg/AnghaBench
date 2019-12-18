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
struct roff_node {scalar_t__ type; int tok; int /*<<< orphan*/  pos; int /*<<< orphan*/  line; struct roff_node* parent; } ;
struct roff_man {int flags; struct roff_node* last; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MANDOCERR_BLK_LINE ; 
 int MAN_BLINE ; 
 int MAN_BSCOPED ; 
 int MAN_ELINE ; 
 int MAN_ESCOPED ; 
 int MAN_NSCOPED ; 
 scalar_t__ MAN_SH ; 
 scalar_t__ MAN_SS ; 
 int MAN_TH ; 
 int MAN_XSCOPE ; 
 scalar_t__ ROFFT_BLOCK ; 
 scalar_t__ ROFFT_HEAD ; 
 scalar_t__ ROFFT_TEXT ; 
 int ROFF_NONOFILL ; 
 int ROFF_fi ; 
 int ROFF_nf ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* man_macro (int) ; 
 int /*<<< orphan*/  man_unscope (struct roff_man*,struct roff_node*) ; 
 int /*<<< orphan*/  mandoc_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  roff_body_alloc (struct roff_man*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/ * roff_name ; 
 int /*<<< orphan*/  roff_node_delete (struct roff_man*,struct roff_node*) ; 

void
man_breakscope(struct roff_man *man, int tok)
{
	struct roff_node *n;

	/*
	 * An element next line scope is open,
	 * and the new macro is not allowed inside elements.
	 * Delete the element that is being broken.
	 */

	if (man->flags & MAN_ELINE && (tok < MAN_TH ||
	    (man_macro(tok)->flags & MAN_NSCOPED) == 0)) {
		n = man->last;
		if (n->type == ROFFT_TEXT)
			n = n->parent;
		if (n->tok < MAN_TH ||
		    (man_macro(n->tok)->flags & (MAN_NSCOPED | MAN_ESCOPED))
		     == MAN_NSCOPED)
			n = n->parent;

		mandoc_msg(MANDOCERR_BLK_LINE, n->line, n->pos,
		    "%s breaks %s", roff_name[tok], roff_name[n->tok]);

		roff_node_delete(man, n);
		man->flags &= ~MAN_ELINE;
	}

	/*
	 * Weird special case:
	 * Switching fill mode closes section headers.
	 */

	if (man->flags & MAN_BLINE &&
	    (tok == ROFF_nf || tok == ROFF_fi) &&
	    (man->last->tok == MAN_SH || man->last->tok == MAN_SS)) {
		n = man->last;
		man_unscope(man, n);
		roff_body_alloc(man, n->line, n->pos, n->tok);
		man->flags &= ~(MAN_BLINE | ROFF_NONOFILL);
	}

	/*
	 * A block header next line scope is open,
	 * and the new macro is not allowed inside block headers.
	 * Delete the block that is being broken.
	 */

	if (man->flags & MAN_BLINE && tok != ROFF_nf && tok != ROFF_fi &&
	    (tok < MAN_TH || man_macro(tok)->flags & MAN_XSCOPE)) {
		n = man->last;
		if (n->type == ROFFT_TEXT)
			n = n->parent;
		if (n->tok < MAN_TH ||
		    (man_macro(n->tok)->flags & MAN_XSCOPE) == 0)
			n = n->parent;

		assert(n->type == ROFFT_HEAD);
		n = n->parent;
		assert(n->type == ROFFT_BLOCK);
		assert(man_macro(n->tok)->flags & MAN_BSCOPED);

		mandoc_msg(MANDOCERR_BLK_LINE, n->line, n->pos,
		    "%s breaks %s", roff_name[tok], roff_name[n->tok]);

		roff_node_delete(man, n);
		man->flags &= ~(MAN_BLINE | ROFF_NONOFILL);
	}
}