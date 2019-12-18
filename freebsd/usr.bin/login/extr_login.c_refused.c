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
struct TYPE_2__ {int /*<<< orphan*/  pw_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_NOTICE ; 
 int /*<<< orphan*/  SLEEP_EXIT ; 
 int /*<<< orphan*/  bail (int /*<<< orphan*/ ,int) ; 
 scalar_t__ hflag ; 
 int /*<<< orphan*/  hostname ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 TYPE_1__* pwd ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  tty ; 

__attribute__((used)) static void
refused(const char *msg, const char *rtype, int lout)
{

	if (msg != NULL)
	    printf("%s.\n", msg);
	if (hflag)
		syslog(LOG_NOTICE, "LOGIN %s REFUSED (%s) FROM %s ON TTY %s",
		    pwd->pw_name, rtype, hostname, tty);
	else
		syslog(LOG_NOTICE, "LOGIN %s REFUSED (%s) ON TTY %s",
		    pwd->pw_name, rtype, tty);
	if (lout)
		bail(SLEEP_EXIT, 1);
}