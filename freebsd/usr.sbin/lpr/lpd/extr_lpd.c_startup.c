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
struct printer {char* printer; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 scalar_t__ ckqueue (struct printer*) ; 
 int firstprinter (struct printer*,int*) ; 
 int fork () ; 
 int /*<<< orphan*/  lastprinter () ; 
 scalar_t__ lflag ; 
 int /*<<< orphan*/  mcleanup (int /*<<< orphan*/ ) ; 
 int nextprinter (struct printer*,int*) ; 
 int /*<<< orphan*/  printjob (struct printer*) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static void
startup(void)
{
	int pid, status, more;
	struct printer myprinter, *pp = &myprinter;

	more = firstprinter(pp, &status);
	if (status)
		goto errloop;
	while (more) {
		if (ckqueue(pp) <= 0) {
			goto next;
		}
		if (lflag)
			syslog(LOG_INFO, "lpd startup: work for %s",
			    pp->printer);
		if ((pid = fork()) < 0) {
			syslog(LOG_WARNING, "lpd startup: cannot fork for %s",
			    pp->printer);
			mcleanup(0);
		}
		if (pid == 0) {
			lastprinter();
			printjob(pp);
			/* NOTREACHED */
		}
		do {
next:
			more = nextprinter(pp, &status);
errloop:
			if (status)
				syslog(LOG_WARNING, 
				    "lpd startup: printcap entry for %s has errors, skipping",
				    pp->printer ? pp->printer : "<noname?>");
		} while (more && status);
	}
}