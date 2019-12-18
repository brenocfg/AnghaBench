#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ cno; } ;
struct TYPE_9__ {TYPE_1__ m_final; } ;
typedef  TYPE_2__ VICMD ;
struct TYPE_11__ {int /*<<< orphan*/  lundo; } ;
struct TYPE_10__ {TYPE_7__* ep; } ;
typedef  TYPE_3__ SCR ;

/* Variables and functions */
 int /*<<< orphan*/  BACKWARD ; 
 int /*<<< orphan*/  F_SET (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_UNDO ; 
 int log_setline (TYPE_3__*) ; 

int
v_Undo(SCR *sp, VICMD *vp)
{
	/*
	 * Historically, U reset the cursor to the first column in the line
	 * (not the first non-blank).  This seems a bit non-intuitive, but,
	 * considering that we may have undone multiple changes, anything
	 * else (including the cursor position stored in the logging records)
	 * is going to appear random.
	 */
	vp->m_final.cno = 0;

	/*
	 * !!!
	 * Set up the flags so that an immediately subsequent 'u' will roll
	 * forward, instead of backward.  In historic vi, a 'u' following a
	 * 'U' redid all of the changes to the line.  Given that the user has
	 * explicitly discarded those changes by entering 'U', it seems likely
	 * that the user wants something between the original and end forms of
	 * the line, so starting to replay the changes seems the best way to
	 * get to there.
	 */
	F_SET(sp->ep, F_UNDO);
	sp->ep->lundo = BACKWARD;

	return (log_setline(sp));
}