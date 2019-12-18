#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
typedef  int /*<<< orphan*/  recno_t ;
typedef  enum nresult { ____Placeholder_nresult } nresult ;
typedef  enum badaddr { ____Placeholder_badaddr } badaddr ;
struct TYPE_10__ {int /*<<< orphan*/ * name; } ;
struct TYPE_9__ {int /*<<< orphan*/ * ep; } ;
typedef  TYPE_1__ SCR ;
typedef  TYPE_2__ EXCMDLIST ;

/* Variables and functions */
#define  A_COMBO 136 
#define  A_EMPTY 135 
#define  A_EOF 134 
#define  A_NOTSET 133 
#define  A_ZERO 132 
 int /*<<< orphan*/  EXM_NOFILEYET ; 
 int /*<<< orphan*/  M_ERR ; 
 int /*<<< orphan*/  M_SYSERR ; 
#define  NUM_ERR 131 
#define  NUM_OK 130 
#define  NUM_OVER 129 
#define  NUM_UNDER 128 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  db_last (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ex_wemsg (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msgq (TYPE_1__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  msgq_wstr (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 

void
ex_badaddr(SCR *sp, const EXCMDLIST *cp, enum badaddr ba, enum nresult nret)
{
	recno_t lno;

	switch (nret) {
	case NUM_OK:
		break;
	case NUM_ERR:
		msgq(sp, M_SYSERR, NULL);
		return;
	case NUM_OVER:
		msgq(sp, M_ERR, "099|Address value overflow");
		return;
	case NUM_UNDER:
		msgq(sp, M_ERR, "100|Address value underflow");
		return;
	}

	/*
	 * When encountering an address error, tell the user if there's no
	 * underlying file, that's the real problem.
	 */
	if (sp->ep == NULL) {
		ex_wemsg(sp, cp ? cp->name : NULL, EXM_NOFILEYET);
		return;
	}

	switch (ba) {
	case A_COMBO:
		msgq(sp, M_ERR, "101|Illegal address combination");
		break;
	case A_EOF:
		if (db_last(sp, &lno))
			return;
		if (lno != 0) {
			msgq(sp, M_ERR,
			    "102|Illegal address: only %lu lines in the file",
			    (u_long)lno);
			break;
		}
		/* FALLTHROUGH */
	case A_EMPTY:
		msgq(sp, M_ERR, "103|Illegal address: the file is empty");
		break;
	case A_NOTSET:
		abort();
		/* NOTREACHED */
	case A_ZERO:
		msgq_wstr(sp, M_ERR, cp->name,
		    "104|The %s command doesn't permit an address of 0");
		break;
	}
	return;
}