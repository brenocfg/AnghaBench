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
typedef  int u_short ;
struct vattr {scalar_t__ va_uid; int va_mode; int /*<<< orphan*/  va_gid; } ;
struct ucred {scalar_t__ cr_uid; } ;
typedef  int /*<<< orphan*/  gid_t ;
typedef  int accmode_t ;

/* Variables and functions */
 int EACCES ; 
 int S_IRGRP ; 
 int S_IROTH ; 
 int S_IRUSR ; 
 int S_IWGRP ; 
 int S_IWOTH ; 
 int S_IWUSR ; 
 int S_IXGRP ; 
 int S_IXOTH ; 
 int S_IXUSR ; 
 int VEXEC ; 
 int VREAD ; 
 int VWRITE ; 
 scalar_t__ groupmember (int /*<<< orphan*/ ,struct ucred*) ; 

__attribute__((used)) static int
unionfs_check_corrected_access(accmode_t accmode,
			     struct vattr *va,
			     struct ucred *cred)
{
	int		count;
	uid_t		uid;	/* upper side vnode's uid */
	gid_t		gid;	/* upper side vnode's gid */
	u_short		vmode;	/* upper side vnode's mode */
	u_short		mask;

	mask = 0;
	uid = va->va_uid;
	gid = va->va_gid;
	vmode = va->va_mode;

	/* check owner */
	if (cred->cr_uid == uid) {
		if (accmode & VEXEC)
			mask |= S_IXUSR;
		if (accmode & VREAD)
			mask |= S_IRUSR;
		if (accmode & VWRITE)
			mask |= S_IWUSR;
		return ((vmode & mask) == mask ? 0 : EACCES);
	}

	/* check group */
	count = 0;
	if (groupmember(gid, cred)) {
		if (accmode & VEXEC)
			mask |= S_IXGRP;
		if (accmode & VREAD)
			mask |= S_IRGRP;
		if (accmode & VWRITE)
			mask |= S_IWGRP;
		return ((vmode & mask) == mask ? 0 : EACCES);
	}

	/* check other */
	if (accmode & VEXEC)
		mask |= S_IXOTH;
	if (accmode & VREAD)
		mask |= S_IROTH;
	if (accmode & VWRITE)
		mask |= S_IWOTH;

	return ((vmode & mask) == mask ? 0 : EACCES);
}