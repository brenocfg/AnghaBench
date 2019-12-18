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
typedef  int /*<<< orphan*/  fnbuf ;

/* Variables and functions */
 int PATH_MAX ; 
 int /*<<< orphan*/  doclean ; 
 long nfiles ; 
 char* prefix ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int,long) ; 
 scalar_t__ sufflen ; 
 int /*<<< orphan*/  unlink (char*) ; 

__attribute__((used)) static void
cleanup(void)
{
	char fnbuf[PATH_MAX];
	long i;

	if (!doclean)
		return;

	/*
	 * NOTE: One cannot portably assume to be able to call snprintf()
	 * from inside a signal handler. It does, however, appear to be safe
	 * to do on FreeBSD. The solution to this problem is worse than the
	 * problem itself.
	 */

	for (i = 0; i < nfiles; i++) {
		snprintf(fnbuf, sizeof(fnbuf), "%s%0*ld", prefix,
		    (int)sufflen, i);
		unlink(fnbuf);
	}
}