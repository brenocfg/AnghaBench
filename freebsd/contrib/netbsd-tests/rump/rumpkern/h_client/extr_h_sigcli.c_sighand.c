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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  __arraycount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  hostnamebuf ; 
 int /*<<< orphan*/  hostnamemib ; 
 int rump_sys___sysctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigexecs ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sighand(int sig)
{
	char buf[128];
	size_t blen = sizeof(buf);

	if (rump_sys___sysctl(hostnamemib, __arraycount(hostnamemib),
	    buf, &blen, NULL, 0) == -1)
		err(1, "sighand sysctl");
	if (strcmp(buf, hostnamebuf) != 0)
		errx(1, "sighandler hostname");
	sigexecs++;
}