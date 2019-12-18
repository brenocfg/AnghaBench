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
typedef  int time_t ;
struct TYPE_2__ {int tv_sec; } ;
struct utmpx {int ut_type; TYPE_1__ ut_tv; int /*<<< orphan*/  ut_host; int /*<<< orphan*/  ut_line; int /*<<< orphan*/  ut_user; } ;
struct tm {int dummy; } ;
struct idtab {int logout; } ;
typedef  int /*<<< orphan*/  ct ;

/* Variables and functions */
#define  BOOT_TIME 132 
#define  NEW_TIME 131 
#define  OLD_TIME 130 
#define  SHUTDOWN_TIME 129 
#define  USER_PROCESS 128 
 int /*<<< orphan*/  crmsg ; 
 int /*<<< orphan*/  ctf (char*) ; 
 scalar_t__ d_first ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 struct tm* gmtime (int*) ; 
 struct tm* localtime (int*) ; 
 int maxrec ; 
 scalar_t__ sflag ; 
 int /*<<< orphan*/  strftime (char*,int,char*,struct tm*) ; 
 int width ; 
 int /*<<< orphan*/  xo_attr (char*,char*,long) ; 
 int /*<<< orphan*/  xo_close_instance (char*) ; 
 int /*<<< orphan*/  xo_emit (char*,...) ; 
 int /*<<< orphan*/  xo_open_instance (char*) ; 
 scalar_t__ yflag ; 

__attribute__((used)) static void
printentry(struct utmpx *bp, struct idtab *tt)
{
	char ct[80];
	struct tm *tm;
	time_t	delta;				/* time difference */
	time_t	t;

	if (maxrec != -1 && !maxrec--)
		exit(0);
	xo_open_instance("last");
	t = bp->ut_tv.tv_sec;
	tm = localtime(&t);
	(void) strftime(ct, sizeof(ct), d_first ?
	    (yflag ? "%a %e %b %Y %R" : "%a %e %b %R") :
	    (yflag ? "%a %b %e %Y %R" : "%a %b %e %R"), tm);
	switch (bp->ut_type) {
	case BOOT_TIME:
		xo_emit("{:user/%-42s/%s}", "boot time");
		break;
	case SHUTDOWN_TIME:
		xo_emit("{:user/%-42s/%s}", "shutdown time");
		break;
	case OLD_TIME:
		xo_emit("{:user/%-42s/%s}", "old time");
		break;
	case NEW_TIME:
		xo_emit("{:user/%-42s/%s}", "new time");
		break;
	case USER_PROCESS:
		xo_emit("{:user/%-10s/%s} {:tty/%-8s/%s} {:from/%-22.22s/%s}",
		    bp->ut_user, bp->ut_line, bp->ut_host);
		break;
	}
	xo_attr("seconds", "%lu", (unsigned long)t);
	xo_emit(ctf(" {:login-time/%s%c/%s}"), ct, tt == NULL ? '\n' : ' ');
	if (tt == NULL)
		goto end;
	if (!tt->logout) {
		xo_emit("  {:logout-time/still logged in}\n");
		goto end;
	}
	if (tt->logout < 0) {
		tt->logout = -tt->logout;
		xo_emit("- {:logout-reason/%s}", crmsg);
	} else {
		tm = localtime(&tt->logout);
		(void) strftime(ct, sizeof(ct), "%R", tm);
		xo_attr("seconds", "%lu", (unsigned long)tt->logout);
		xo_emit(ctf("- {:logout-time/%s}"), ct);
	}
	delta = tt->logout - bp->ut_tv.tv_sec;
	xo_attr("seconds", "%ld", (long)delta);
	if (sflag) {
		xo_emit("  ({:session-length/%8ld})\n", (long)delta);
	} else {
		tm = gmtime(&delta);
		(void) strftime(ct, sizeof(ct), width >= 8 ? "%T" : "%R", tm);
		if (delta < 86400)
			xo_emit(ctf("  ({:session-length/%s})\n"), ct);
		else
			xo_emit(ctf(" ({:session-length/%ld+%s})\n"),
			    (long)delta / 86400, ct);
	}

end:
	xo_close_instance("last");
}