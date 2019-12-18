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
typedef  scalar_t__ uid_t ;

/* Variables and functions */
 int ENOSYS ; 
 int errno ; 
 int /*<<< orphan*/  error (char*,scalar_t__,char*) ; 
 scalar_t__ seteuid (scalar_t__) ; 
 scalar_t__ setreuid (scalar_t__,scalar_t__) ; 
 scalar_t__ setuid (scalar_t__) ; 
 char* strerror (int) ; 

int
setresuid(uid_t ruid, uid_t euid, uid_t suid)
{
	int ret = 0, saved_errno;

	if (ruid != suid) {
		errno = ENOSYS;
		return -1;
	}
#if defined(HAVE_SETREUID) && !defined(BROKEN_SETREUID)
	if (setreuid(ruid, euid) < 0) {
		saved_errno = errno;
		error("setreuid %u: %.100s", ruid, strerror(errno));
		errno = saved_errno;
		ret = -1;
	}
#else

# ifndef SETEUID_BREAKS_SETUID
	if (seteuid(euid) < 0) {
		saved_errno = errno;
		error("seteuid %u: %.100s", euid, strerror(errno));
		errno = saved_errno;
		ret = -1;
	}
# endif
	if (setuid(ruid) < 0) {
		saved_errno = errno;
		error("setuid %u: %.100s", ruid, strerror(errno));
		errno = saved_errno;
		ret = -1;
	}
#endif
	return ret;
}