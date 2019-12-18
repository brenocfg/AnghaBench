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
typedef  scalar_t__ u_int ;
typedef  scalar_t__ gid_t ;

/* Variables and functions */
 int ENOSYS ; 
 int errno ; 
 int /*<<< orphan*/  error (char*,scalar_t__,char*) ; 
 scalar_t__ setegid (scalar_t__) ; 
 scalar_t__ setgid (scalar_t__) ; 
 scalar_t__ setregid (scalar_t__,scalar_t__) ; 
 char* strerror (int) ; 

int
setresgid(gid_t rgid, gid_t egid, gid_t sgid)
{
	int ret = 0, saved_errno;

	if (rgid != sgid) {
		errno = ENOSYS;
		return -1;
	}
#if defined(HAVE_SETREGID) && !defined(BROKEN_SETREGID)
	if (setregid(rgid, egid) < 0) {
		saved_errno = errno;
		error("setregid %u: %.100s", rgid, strerror(errno));
		errno = saved_errno;
		ret = -1;
	}
#else
	if (setegid(egid) < 0) {
		saved_errno = errno;
		error("setegid %u: %.100s", (u_int)egid, strerror(errno));
		errno = saved_errno;
		ret = -1;
	}
	if (setgid(rgid) < 0) {
		saved_errno = errno;
		error("setgid %u: %.100s", rgid, strerror(errno));
		errno = saved_errno;
		ret = -1;
	}
#endif
	return ret;
}