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
struct TYPE_5__ {int ttyfd; TYPE_1__* pw; } ;
struct TYPE_4__ {int /*<<< orphan*/  pw_name; } ;
typedef  TYPE_2__ Session ;

/* Variables and functions */
 int /*<<< orphan*/  _PATH_PASSWD_PROG ; 
 int /*<<< orphan*/  execl (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  setexeccon (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
do_pwchange(Session *s)
{
	fflush(NULL);
	fprintf(stderr, "WARNING: Your password has expired.\n");
	if (s->ttyfd != -1) {
		fprintf(stderr,
		    "You must change your password now and login again!\n");
#ifdef WITH_SELINUX
		setexeccon(NULL);
#endif
#ifdef PASSWD_NEEDS_USERNAME
		execl(_PATH_PASSWD_PROG, "passwd", s->pw->pw_name,
		    (char *)NULL);
#else
		execl(_PATH_PASSWD_PROG, "passwd", (char *)NULL);
#endif
		perror("passwd");
	} else {
		fprintf(stderr,
		    "Password change required but no TTY available.\n");
	}
	exit(1);
}