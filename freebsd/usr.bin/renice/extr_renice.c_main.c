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
struct passwd {int pw_uid; } ;

/* Variables and functions */
 int PRIO_PGRP ; 
 int PRIO_PROCESS ; 
 int PRIO_USER ; 
 scalar_t__ donice (int,int,int,int) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ getnum (char*,char*,int*) ; 
 struct passwd* getpwnam (char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

int
main(int argc, char *argv[])
{
	struct passwd *pwd;
	int errs, incr, prio, which, who;

	errs = 0;
	incr = 0;
	which = PRIO_PROCESS;
	who = 0;
	argc--, argv++;
	if (argc < 2)
		usage();
	if (strcmp(*argv, "-n") == 0) {
		incr = 1;
		argc--, argv++;
		if (argc < 2)
			usage();
	}
	if (getnum("priority", *argv, &prio))
		return (1);
	argc--, argv++;
	for (; argc > 0; argc--, argv++) {
		if (strcmp(*argv, "-g") == 0) {
			which = PRIO_PGRP;
			continue;
		}
		if (strcmp(*argv, "-u") == 0) {
			which = PRIO_USER;
			continue;
		}
		if (strcmp(*argv, "-p") == 0) {
			which = PRIO_PROCESS;
			continue;
		}
		if (which == PRIO_USER) {
			if ((pwd = getpwnam(*argv)) != NULL)
				who = pwd->pw_uid;
			else if (getnum("uid", *argv, &who)) {
				errs++;
				continue;
			} else if (who < 0) {
				warnx("%s: bad value", *argv);
				errs++;
				continue;
			}
		} else {
			if (getnum("pid", *argv, &who)) {
				errs++;
				continue;
			}
			if (who < 0) {
				warnx("%s: bad value", *argv);
				errs++;
				continue;
			}
		}
		errs += donice(which, who, prio, incr);
	}
	exit(errs != 0);
}