#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ recno_t ;
struct TYPE_10__ {scalar_t__ c_nlines; } ;
struct TYPE_9__ {int /*<<< orphan*/  tiq; TYPE_3__* ep; } ;
struct TYPE_8__ {scalar_t__ lno; } ;
typedef  TYPE_1__ TEXT ;
typedef  TYPE_2__ SCR ;
typedef  TYPE_3__ EXF ;

/* Variables and functions */
 int /*<<< orphan*/  EXM_NOFILEYET ; 
 scalar_t__ F_ISSET (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ OOBLNO ; 
 int /*<<< orphan*/  SC_TINPUT ; 
 scalar_t__ TAILQ_FIRST (int /*<<< orphan*/ ) ; 
 scalar_t__ TAILQ_LAST (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _texth ; 
 int /*<<< orphan*/  db_get (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ex_emsg (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
db_exist(
	SCR *sp,
	recno_t lno)
{
	EXF *ep;

	/* Check for no underlying file. */
	if ((ep = sp->ep) == NULL) {
		ex_emsg(sp, NULL, EXM_NOFILEYET);
		return (1);
	}

	if (lno == OOBLNO)
		return (0);
		
	/*
	 * Check the last-line number cache.  Adjust the cached line
	 * number for the lines used by the text input buffers.
	 */
	if (ep->c_nlines != OOBLNO)
		return (lno <= (F_ISSET(sp, SC_TINPUT) ?
		    ep->c_nlines + (((TEXT *)TAILQ_LAST(sp->tiq, _texth))->lno -
		    ((TEXT *)TAILQ_FIRST(sp->tiq))->lno) : ep->c_nlines));

	/* Go get the line. */
	return (!db_get(sp, lno, 0, NULL, NULL));
}