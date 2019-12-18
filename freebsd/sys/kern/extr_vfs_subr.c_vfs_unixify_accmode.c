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
typedef  int accmode_t ;

/* Variables and functions */
 int EPERM ; 
 int VADMIN ; 
 int VADMIN_PERMS ; 
 int VDELETE ; 
 int VDELETE_CHILD ; 
 int VEXPLICIT_DENY ; 
 int VSTAT_PERMS ; 
 int VSYNCHRONIZE ; 

int
vfs_unixify_accmode(accmode_t *accmode)
{
	/*
	 * There is no way to specify explicit "deny" rule using
	 * file mode or POSIX.1e ACLs.
	 */
	if (*accmode & VEXPLICIT_DENY) {
		*accmode = 0;
		return (0);
	}

	/*
	 * None of these can be translated into usual access bits.
	 * Also, the common case for NFSv4 ACLs is to not contain
	 * either of these bits. Caller should check for VWRITE
	 * on the containing directory instead.
	 */
	if (*accmode & (VDELETE_CHILD | VDELETE))
		return (EPERM);

	if (*accmode & VADMIN_PERMS) {
		*accmode &= ~VADMIN_PERMS;
		*accmode |= VADMIN;
	}

	/*
	 * There is no way to deny VREAD_ATTRIBUTES, VREAD_ACL
	 * or VSYNCHRONIZE using file mode or POSIX.1e ACL.
	 */
	*accmode &= ~(VSTAT_PERMS | VSYNCHRONIZE);

	return (0);
}