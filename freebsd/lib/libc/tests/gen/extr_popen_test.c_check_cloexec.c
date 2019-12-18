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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_CHECK_MSG (int,char*,int,...) ; 
 int FD_CLOEXEC ; 
 int /*<<< orphan*/  F_GETFD ; 
 int /*<<< orphan*/  errno ; 
 int fcntl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * strchr (char const*,char) ; 

__attribute__((used)) static void
check_cloexec(FILE *fp, const char *mode)
{
	int exp_flags, flags;

	flags = fcntl(fileno(fp), F_GETFD);
	ATF_CHECK_MSG(flags != -1, "fcntl(F_GETFD) failed; errno=%d", errno);
	if (flags == -1)
		return;
	if (strchr(mode, 'e') != NULL)
		exp_flags = FD_CLOEXEC;
	else
		exp_flags = 0;
	ATF_CHECK_MSG((flags & FD_CLOEXEC) == exp_flags,
	    "bad cloexec flag; %d != %d", flags, exp_flags);
}