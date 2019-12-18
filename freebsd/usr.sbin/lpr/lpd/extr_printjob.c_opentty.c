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
struct printer {int /*<<< orphan*/  printer; int /*<<< orphan*/  lp; scalar_t__ rw; } ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  O_WRONLY ; 
 int /*<<< orphan*/  delay (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ isatty (scalar_t__) ; 
 scalar_t__ open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pfd ; 
 int /*<<< orphan*/  pstatus (struct printer const*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setty (struct printer const*) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
opentty(const struct printer *pp)
{
	register int i;

	for (i = 1; ; i = i < 32 ? i << 1 : i) {
		pfd = open(pp->lp, pp->rw ? O_RDWR : O_WRONLY);
		if (pfd >= 0) {
			delay(500);
			break;
		}
		if (errno == ENOENT) {
			syslog(LOG_ERR, "%s: %m", pp->lp);
			exit(1);
		}
		if (i == 1)
			pstatus(pp, 
				"waiting for %s to become ready (offline?)",
				pp->printer);
		sleep(i);
	}
	if (isatty(pfd))
		setty(pp);
	pstatus(pp, "%s is ready and printing", pp->printer);
}