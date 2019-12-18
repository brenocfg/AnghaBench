#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int recno_t ;
struct TYPE_7__ {int lno; } ;
struct TYPE_6__ {int lno; scalar_t__ cno; } ;
typedef  int /*<<< orphan*/  TEXTH ;
typedef  TYPE_1__ SCR ;

/* Variables and functions */
 int /*<<< orphan*/  F_SET (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SC_SCR_REDRAW ; 
 TYPE_4__* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  db_exist (TYPE_1__*,int) ; 

__attribute__((used)) static void
txt_err(SCR *sp, TEXTH *tiqh)
{
	recno_t lno;

	/*
	 * The problem with input processing is that the cursor is at an
	 * indeterminate position since some input may have been lost due
	 * to a malloc error.  So, try to go back to the place from which
	 * the cursor started, knowing that it may no longer be available.
	 *
	 * We depend on at least one line number being set in the text
	 * chain.
	 */
	for (lno = TAILQ_FIRST(tiqh)->lno;
	    !db_exist(sp, lno) && lno > 0; --lno);

	sp->lno = lno == 0 ? 1 : lno;
	sp->cno = 0;

	/* Redraw the screen, just in case. */
	F_SET(sp, SC_SCR_REDRAW);
}