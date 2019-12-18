#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  int /*<<< orphan*/  VI_PRIVATE ;
struct TYPE_8__ {size_t len; size_t sv_len; scalar_t__ owrite; scalar_t__ insert; scalar_t__ lno; int /*<<< orphan*/ * lb; } ;
typedef  int /*<<< orphan*/  TEXTH ;
typedef  TYPE_1__ TEXT ;
typedef  int /*<<< orphan*/  SCR ;

/* Variables and functions */
 int /*<<< orphan*/  CH_CURSOR ; 
 int /*<<< orphan*/  FL_CLR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FL_ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FL_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LINE_DELETE ; 
 int /*<<< orphan*/  M_BERR ; 
 TYPE_1__* TAILQ_PREV (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TXT_APPENDEOL ; 
 int /*<<< orphan*/  TXT_REPLAY ; 
 int /*<<< orphan*/ * VIP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _texth ; 
 int /*<<< orphan*/  msgq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  q ; 
 int /*<<< orphan*/  text_free (TYPE_1__*) ; 
 scalar_t__ vs_change (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static TEXT *
txt_backup(SCR *sp, TEXTH *tiqh, TEXT *tp, u_int32_t *flagsp)
{
	VI_PRIVATE *vip;
	TEXT *ntp;

	/* Get a handle on the previous TEXT structure. */
	if ((ntp = TAILQ_PREV(tp, _texth, q)) == NULL) {
		if (!FL_ISSET(*flagsp, TXT_REPLAY))
			msgq(sp, M_BERR,
			    "193|Already at the beginning of the insert");
		return (tp);
	}

	/* Bookkeeping. */
	ntp->len = ntp->sv_len;

	/* Handle appending to the line. */
	vip = VIP(sp);
	if (ntp->owrite == 0 && ntp->insert == 0) {
		ntp->lb[ntp->len] = CH_CURSOR;
		++ntp->insert;
		++ntp->len;
		FL_SET(*flagsp, TXT_APPENDEOL);
	} else
		FL_CLR(*flagsp, TXT_APPENDEOL);

	/* Release the current TEXT. */
	TAILQ_REMOVE(tiqh, tp, q);
	text_free(tp);

	/* Update the old line on the screen. */
	if (vs_change(sp, ntp->lno + 1, LINE_DELETE))
		return (NULL);

	/* Return the new/current TEXT. */
	return (ntp);
}