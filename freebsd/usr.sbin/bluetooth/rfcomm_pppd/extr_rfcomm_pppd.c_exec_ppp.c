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

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ dup (int) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ execv (char*,char**) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,char*,char*,...) ; 

__attribute__((used)) static void
exec_ppp(int s, char *unit, char *label)
{
	char	 ppp[] = "/usr/sbin/ppp";
	char	*ppp_args[] = { ppp,  "-direct", "-quiet",
				NULL, NULL,      NULL,     NULL };

	close(0);
	if (dup(s) < 0) {
		syslog(LOG_ERR, "Could not dup(0). %s (%d)",
			strerror(errno), errno);
		exit(1);
	}

	close(1);
	if (dup(s) < 0) {
		syslog(LOG_ERR, "Could not dup(1). %s (%d)",
			strerror(errno), errno);
		exit(1);
	}

	close(2);
	open("/dev/null", O_RDWR);

	if (unit != NULL) {
		ppp_args[3] = "-unit";
		ppp_args[4] = unit;
		ppp_args[5] = label;
	} else
		ppp_args[3] = label;

	if (execv(ppp, ppp_args) < 0) {
		syslog(LOG_ERR, "Could not exec(%s -direct -quiet%s%s %s). " \
			"%s (%d)", ppp, (unit != NULL)? " -unit " : "",
			(unit != NULL)? unit : "", label,
			strerror(errno), errno);
		exit(1);
	}
}