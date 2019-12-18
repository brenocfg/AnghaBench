#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
typedef  int /*<<< orphan*/  nbuf ;
typedef  int /*<<< orphan*/  VI_PRIVATE ;
struct TYPE_17__ {int /*<<< orphan*/  (* scr_move ) (TYPE_2__*,size_t,size_t) ;int /*<<< orphan*/  (* scr_addstr ) (TYPE_2__*,char*,size_t) ;int /*<<< orphan*/  (* scr_cursor ) (TYPE_2__*,size_t*,size_t*) ;} ;
struct TYPE_16__ {TYPE_3__* gp; } ;
struct TYPE_15__ {int lno; scalar_t__ coff; int soff; } ;
typedef  TYPE_1__ SMAP ;
typedef  TYPE_2__ SCR ;
typedef  TYPE_3__ GS ;

/* Variables and functions */
 scalar_t__ F_ISSET (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* HMAP ; 
 scalar_t__ O_ISSET (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  O_LEFTRIGHT ; 
 char* O_NUMBER_FMT ; 
 int /*<<< orphan*/  SC_TINPUT_INFO ; 
 TYPE_1__* TMAP ; 
 int /*<<< orphan*/ * VIP (TYPE_2__*) ; 
 int db_exist (TYPE_2__*,int) ; 
 size_t snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,size_t*,size_t*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,int,size_t) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__*,char*,size_t) ; 
 int /*<<< orphan*/  stub4 (TYPE_2__*,size_t,size_t) ; 

int
vs_number(SCR *sp)
{
	GS *gp;
	SMAP *smp;
	VI_PRIVATE *vip;
	size_t len, oldy, oldx;
	int exist;
	char nbuf[10];

	gp = sp->gp;
	vip = VIP(sp);

	/* No reason to do anything if we're in input mode on the info line. */
	if (F_ISSET(sp, SC_TINPUT_INFO))
		return (0);

	/*
	 * Try and avoid getting the last line in the file, by getting the
	 * line after the last line in the screen -- if it exists, we know
	 * we have to to number all the lines in the screen.  Get the one
	 * after the last instead of the last, so that the info line doesn't
	 * fool us.  (The problem is that file_lline will lie, and tell us
	 * that the info line is the last line in the file.) If that test
	 * fails, we have to check each line for existence.
	 */
	exist = db_exist(sp, TMAP->lno + 1);

	(void)gp->scr_cursor(sp, &oldy, &oldx);
	for (smp = HMAP; smp <= TMAP; ++smp) {
		/* Numbers are only displayed for the first screen line. */
		if (O_ISSET(sp, O_LEFTRIGHT)) {
			if (smp->coff != 0)
				continue;
		} else
			if (smp->soff != 1)
				continue;

		/*
		 * The first line of an empty file gets numbered, otherwise
		 * number any existing line.
		 */
		if (smp->lno != 1 && !exist && !db_exist(sp, smp->lno))
			break;

		(void)gp->scr_move(sp, smp - HMAP, 0);
		len = snprintf(nbuf, sizeof(nbuf), O_NUMBER_FMT, (u_long)smp->lno);
		(void)gp->scr_addstr(sp, nbuf, len);
	}
	(void)gp->scr_move(sp, oldy, oldx);
	return (0);
}