#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ sl_cur; } ;

/* Variables and functions */
 int /*<<< orphan*/  argbase ; 
 int /*<<< orphan*/  argbuf ; 
 int cursor_argc ; 
 scalar_t__ cursor_argo ; 
 int /*<<< orphan*/ * cursor_pos ; 
 int /*<<< orphan*/  ftp_sl_add (TYPE_1__*,char*) ; 
 int /*<<< orphan*/ * line ; 
 TYPE_1__* marg_sl ; 
 int margc ; 
 int /*<<< orphan*/ * margv ; 
 scalar_t__ slrflag ; 
 char* slurpstring () ; 
 int /*<<< orphan*/ * stringbase ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

void
makeargv(void)
{
	char *argp;

	stringbase = line;		/* scan from first of buffer */
	argbase = argbuf;		/* store from first of buffer */
	slrflag = 0;
	marg_sl->sl_cur = 0;		/* reset to start of marg_sl */
	for (margc = 0; ; margc++) {
		argp = slurpstring();
		ftp_sl_add(marg_sl, argp);
		if (argp == NULL)
			break;
	}
#ifndef NO_EDITCOMPLETE
	if (cursor_pos == line) {
		cursor_argc = 0;
		cursor_argo = 0;
	} else if (cursor_pos != NULL) {
		cursor_argc = margc;
		cursor_argo = strlen(margv[margc-1]);
	}
#endif /* !NO_EDITCOMPLETE */
}