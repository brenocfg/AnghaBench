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
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int /*<<< orphan*/  CGETS (int,int,char*) ; 
 scalar_t__ GoodStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PUTPURE ; 
 int /*<<< orphan*/  Str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T_CanIns ; 
 int /*<<< orphan*/  T_IC ; 
 int /*<<< orphan*/  T_ei ; 
 int /*<<< orphan*/  T_ic ; 
 int /*<<< orphan*/  T_im ; 
 int /*<<< orphan*/  T_ip ; 
 int TermH ; 
 int /*<<< orphan*/  flush () ; 
 int /*<<< orphan*/  so_write (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tgoto (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  tputs (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xprintf (int /*<<< orphan*/ ,...) ; 

void
Insert_write(Char *cp, int num)
{
    if (num <= 0)
	return;
    if (!T_CanIns) {
#ifdef DEBUG_EDIT
	xprintf(CGETS(7, 18, "ERROR: cannot insert\r\n"));
#endif /* DEBUG_EDIT */
	flush();
	return;
    }

    if (num > TermH) {
#ifdef DEBUG_SCREEN
	xprintf(CGETS(7, 19, "StartInsert: num is riduculous: %d\r\n"), num);
	flush();
#endif /* DEBUG_SCREEN */
	return;
    }

    if (GoodStr(T_IC))		/* if I have multiple insert */
	if ((num > 1) || !GoodStr(T_ic)) {	/* if ic would be more expen. */
	    (void) tputs(tgoto(Str(T_IC), num, num), num, PUTPURE);
	    so_write(cp, num);	/* this updates CursorH/V */
	    return;
	}

    if (GoodStr(T_im) && GoodStr(T_ei)) { /* if I have insert mode */
	(void) tputs(Str(T_im), 1, PUTPURE);

	so_write(cp, num);	/* this updates CursorH/V */

	if (GoodStr(T_ip))	/* have to make num chars insert */
	    (void) tputs(Str(T_ip), 1, PUTPURE);

	(void) tputs(Str(T_ei), 1, PUTPURE);
	return;
    }

    do {
	if (GoodStr(T_ic))	/* have to make num chars insert */
	    (void) tputs(Str(T_ic), 1, PUTPURE);	/* insert a char */

	so_write(cp++, 1);	/* this updates CursorH/V */

	if (GoodStr(T_ip))	/* have to make num chars insert */
	    (void) tputs(Str(T_ip), 1, PUTPURE);/* pad the inserted char */

    } while (--num);

}