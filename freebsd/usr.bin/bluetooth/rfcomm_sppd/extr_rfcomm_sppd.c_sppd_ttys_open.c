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
struct termios {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  cfmakeraw (struct termios*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int openpty (int*,int*,char*,struct termios*,int /*<<< orphan*/ *) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sppd_ttys_open(char **tty, int *amaster, int *aslave)
{
	char		 pty[PATH_MAX];
	struct termios	 tio;

	cfmakeraw(&tio);

	if (openpty(amaster, aslave, pty, &tio, NULL) == -1) {
		syslog(LOG_ERR, "Could not openpty(). %s", strerror(errno));
		return (-1);
	}

	if ((*tty = strdup(pty)) == NULL) {
		syslog(LOG_ERR, "Could not strdup(). %s", strerror(errno));
		close(*aslave);
		close(*amaster);
		return (-1);
	}

	return (0);
}