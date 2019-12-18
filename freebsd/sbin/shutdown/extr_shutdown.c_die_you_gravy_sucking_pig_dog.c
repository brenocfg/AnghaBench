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
 int /*<<< orphan*/  LOG_NOTICE ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  SIGUSR2 ; 
 int /*<<< orphan*/  SIGWINCH ; 
 int /*<<< orphan*/  _PATH_HALT ; 
 int /*<<< orphan*/  _PATH_REBOOT ; 
 scalar_t__ docycle ; 
 scalar_t__ dohalt ; 
 scalar_t__ dopower ; 
 scalar_t__ doreboot ; 
 int /*<<< orphan*/  execle (int /*<<< orphan*/ ,char*,char*,char*,char*,...) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finish (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kill (int,int /*<<< orphan*/ ) ; 
 scalar_t__ killflg ; 
 int /*<<< orphan*/  mbuf ; 
 int /*<<< orphan*/ * nosync ; 
 int /*<<< orphan*/  oflag ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  warn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  whom ; 

__attribute__((used)) static void
die_you_gravy_sucking_pig_dog(void)
{
	char *empty_environ[] = { NULL };

	syslog(LOG_NOTICE, "%s by %s: %s",
	    doreboot ? "reboot" : dohalt ? "halt" : dopower ? "power-down" :
	    docycle ? "power-cycle" : "shutdown", whom, mbuf);

	(void)printf("\r\nSystem shutdown time has arrived\007\007\r\n");
	if (killflg) {
		(void)printf("\rbut you'll have to do it yourself\r\n");
		exit(0);
	}
#ifdef DEBUG
	if (doreboot)
		(void)printf("reboot");
	else if (docycle)
		(void)printf("power-cycle");
	else if (dohalt)
		(void)printf("halt");
	else if (dopower)
		(void)printf("power-down");
	if (nosync != NULL)
		(void)printf(" no sync");
	(void)printf("\nkill -HUP 1\n");
#else
	if (!oflag) {
		(void)kill(1, doreboot ? SIGINT :	/* reboot */
			      dohalt ? SIGUSR1 :	/* halt */
			      dopower ? SIGUSR2 :	/* power-down */
			      docycle ? SIGWINCH :	/* power-cycle */
			      SIGTERM);			/* single-user */
	} else {
		if (doreboot) {
			execle(_PATH_REBOOT, "reboot", "-l", nosync, 
				(char *)NULL, empty_environ);
			syslog(LOG_ERR, "shutdown: can't exec %s: %m.",
				_PATH_REBOOT);
			warn(_PATH_REBOOT);
		}
		else if (dohalt) {
			execle(_PATH_HALT, "halt", "-l", nosync,
				(char *)NULL, empty_environ);
			syslog(LOG_ERR, "shutdown: can't exec %s: %m.",
				_PATH_HALT);
			warn(_PATH_HALT);
		}
		else if (dopower) {
			execle(_PATH_HALT, "halt", "-l", "-p", nosync,
				(char *)NULL, empty_environ);
			syslog(LOG_ERR, "shutdown: can't exec %s: %m.",
				_PATH_HALT);
			warn(_PATH_HALT);
		}
		else if (docycle) {
			execle(_PATH_HALT, "halt", "-l", "-c", nosync,
				(char *)NULL, empty_environ);
			syslog(LOG_ERR, "shutdown: can't exec %s: %m.",
				_PATH_HALT);
			warn(_PATH_HALT);
		}
		(void)kill(1, SIGTERM);		/* to single-user */
	}
#endif
	finish(0);
}