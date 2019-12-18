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
typedef  int /*<<< orphan*/  lockr_t ;
typedef  int /*<<< orphan*/  SCR ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EWOULDBLOCK ; 
 int /*<<< orphan*/  F_SETFD ; 
 int LOCK_EX ; 
 int /*<<< orphan*/  LOCK_FAILED ; 
 int LOCK_NB ; 
 int /*<<< orphan*/  LOCK_SUCCESS ; 
 int /*<<< orphan*/  LOCK_UNAVAIL ; 
 int /*<<< orphan*/  O_ISSET (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  O_LOCKFILES ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fcntl (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  flock (int,int) ; 

lockr_t
file_lock(
	SCR *sp,
	char *name,
	int fd,
	int iswrite)
{
	if (!O_ISSET(sp, O_LOCKFILES))
		return (LOCK_SUCCESS);
	
	/*
	 * !!!
	 * We need to distinguish a lock not being available for the file
	 * from the file system not supporting locking.  Flock is documented
	 * as returning EWOULDBLOCK; add EAGAIN for good measure, and assume
	 * they are the former.  There's no portable way to do this.
	 */
	errno = 0;
	if (!flock(fd, LOCK_EX | LOCK_NB)) {
		fcntl(fd, F_SETFD, 1);
		return (LOCK_SUCCESS);
	}
	return (errno == EAGAIN
#ifdef EWOULDBLOCK
	    || errno == EWOULDBLOCK
#endif
	    ? LOCK_UNAVAIL : LOCK_FAILED);
}