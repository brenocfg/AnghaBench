#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct roff_man {int flags; TYPE_1__* last; } ;
struct TYPE_6__ {int flags; } ;
struct TYPE_5__ {scalar_t__ type; int /*<<< orphan*/  tok; } ;
struct TYPE_4__ {int /*<<< orphan*/  tok; TYPE_2__* parent; } ;

/* Variables and functions */
 int MAN_BLINE ; 
 int MAN_ELINE ; 
 int MAN_ESCOPED ; 
 scalar_t__ ROFFT_ROOT ; 
 int ROFF_NONOFILL ; 
 int /*<<< orphan*/ * man_hasc (char*) ; 
 TYPE_3__* man_macro (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  man_unscope (struct roff_man*,TYPE_2__*) ; 
 int /*<<< orphan*/  roff_body_alloc (struct roff_man*,int,int,int /*<<< orphan*/ ) ; 

void
man_descope(struct roff_man *man, int line, int offs, char *start)
{
	/* Trailing \c keeps next-line scope open. */

	if (start != NULL && man_hasc(start) != NULL)
		return;

	/*
	 * Co-ordinate what happens with having a next-line scope open:
	 * first close out the element scopes (if applicable),
	 * then close out the block scope (also if applicable).
	 */

	if (man->flags & MAN_ELINE) {
		while (man->last->parent->type != ROFFT_ROOT &&
		    man_macro(man->last->parent->tok)->flags & MAN_ESCOPED)
			man_unscope(man, man->last->parent);
		man->flags &= ~MAN_ELINE;
	}
	if ( ! (man->flags & MAN_BLINE))
		return;
	man_unscope(man, man->last->parent);
	roff_body_alloc(man, line, offs, man->last->tok);
	man->flags &= ~(MAN_BLINE | ROFF_NONOFILL);
}