#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct p_times {int dummy; } ;
typedef  int /*<<< orphan*/  pidname ;
struct TYPE_5__ {double pt_pctcpu; TYPE_1__* pt_kp; } ;
struct TYPE_4__ {char* ki_comm; int /*<<< orphan*/  ki_uid; } ;

/* Variables and functions */
 int /*<<< orphan*/  compar ; 
 int getmaxy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvwaddstr (int /*<<< orphan*/ ,int,int,char const*) ; 
 int nproc ; 
 TYPE_2__* pt ; 
 int /*<<< orphan*/  qsort (TYPE_2__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 char* user_from_uid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  waddch (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  wclrtobot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wclrtoeol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  wnd ; 

void
showpigs(void)
{
	int i, j, y, k;
	const char *uname, *pname;
	char pidname[30];

	if (pt == NULL)
		return;

	qsort(pt, nproc, sizeof (struct p_times), compar);
	y = 1;
	i = nproc;
	if (i > getmaxy(wnd)-2)
		i = getmaxy(wnd)-2;
	for (k = 0; i > 0 && pt[k].pt_pctcpu > 0.01; i--, y++, k++) {
		uname = user_from_uid(pt[k].pt_kp->ki_uid, 0);
		pname = pt[k].pt_kp->ki_comm;
		wmove(wnd, y, 0);
		wclrtoeol(wnd);
		mvwaddstr(wnd, y, 0, uname);
		snprintf(pidname, sizeof(pidname), "%10.10s", pname);
		mvwaddstr(wnd, y, 9, pidname);
		wmove(wnd, y, 20);
		for (j = pt[k].pt_pctcpu * 50 + 0.5; j > 0; j--)
			waddch(wnd, 'X');
	}
	wmove(wnd, y, 0); wclrtobot(wnd);
}