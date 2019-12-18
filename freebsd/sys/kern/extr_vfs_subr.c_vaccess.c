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
struct ucred {scalar_t__ cr_uid; } ;
typedef  int mode_t ;
typedef  int /*<<< orphan*/  gid_t ;
typedef  enum vtype { ____Placeholder_vtype } vtype ;
typedef  int accmode_t ;

/* Variables and functions */
 int EACCES ; 
 int EPERM ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  PRIV_VFS_ADMIN ; 
 int /*<<< orphan*/  PRIV_VFS_EXEC ; 
 int /*<<< orphan*/  PRIV_VFS_LOOKUP ; 
 int /*<<< orphan*/  PRIV_VFS_READ ; 
 int /*<<< orphan*/  PRIV_VFS_WRITE ; 
 int S_IRGRP ; 
 int S_IROTH ; 
 int S_IRUSR ; 
 int S_IWGRP ; 
 int S_IWOTH ; 
 int S_IWUSR ; 
 int S_IXGRP ; 
 int S_IXOTH ; 
 int S_IXUSR ; 
 int VADMIN ; 
 int VAPPEND ; 
 int VDIR ; 
 int VEXEC ; 
 int VREAD ; 
 int VWRITE ; 
 scalar_t__ groupmember (int /*<<< orphan*/ ,struct ucred*) ; 
 int /*<<< orphan*/  priv_check_cred (struct ucred*,int /*<<< orphan*/ ) ; 

int
vaccess(enum vtype type, mode_t file_mode, uid_t file_uid, gid_t file_gid,
    accmode_t accmode, struct ucred *cred, int *privused)
{
	accmode_t dac_granted;
	accmode_t priv_granted;

	KASSERT((accmode & ~(VEXEC | VWRITE | VREAD | VADMIN | VAPPEND)) == 0,
	    ("invalid bit in accmode"));
	KASSERT((accmode & VAPPEND) == 0 || (accmode & VWRITE),
	    ("VAPPEND without VWRITE"));

	/*
	 * Look for a normal, non-privileged way to access the file/directory
	 * as requested.  If it exists, go with that.
	 */

	if (privused != NULL)
		*privused = 0;

	dac_granted = 0;

	/* Check the owner. */
	if (cred->cr_uid == file_uid) {
		dac_granted |= VADMIN;
		if (file_mode & S_IXUSR)
			dac_granted |= VEXEC;
		if (file_mode & S_IRUSR)
			dac_granted |= VREAD;
		if (file_mode & S_IWUSR)
			dac_granted |= (VWRITE | VAPPEND);

		if ((accmode & dac_granted) == accmode)
			return (0);

		goto privcheck;
	}

	/* Otherwise, check the groups (first match) */
	if (groupmember(file_gid, cred)) {
		if (file_mode & S_IXGRP)
			dac_granted |= VEXEC;
		if (file_mode & S_IRGRP)
			dac_granted |= VREAD;
		if (file_mode & S_IWGRP)
			dac_granted |= (VWRITE | VAPPEND);

		if ((accmode & dac_granted) == accmode)
			return (0);

		goto privcheck;
	}

	/* Otherwise, check everyone else. */
	if (file_mode & S_IXOTH)
		dac_granted |= VEXEC;
	if (file_mode & S_IROTH)
		dac_granted |= VREAD;
	if (file_mode & S_IWOTH)
		dac_granted |= (VWRITE | VAPPEND);
	if ((accmode & dac_granted) == accmode)
		return (0);

privcheck:
	/*
	 * Build a privilege mask to determine if the set of privileges
	 * satisfies the requirements when combined with the granted mask
	 * from above.  For each privilege, if the privilege is required,
	 * bitwise or the request type onto the priv_granted mask.
	 */
	priv_granted = 0;

	if (type == VDIR) {
		/*
		 * For directories, use PRIV_VFS_LOOKUP to satisfy VEXEC
		 * requests, instead of PRIV_VFS_EXEC.
		 */
		if ((accmode & VEXEC) && ((dac_granted & VEXEC) == 0) &&
		    !priv_check_cred(cred, PRIV_VFS_LOOKUP))
			priv_granted |= VEXEC;
	} else {
		/*
		 * Ensure that at least one execute bit is on. Otherwise,
		 * a privileged user will always succeed, and we don't want
		 * this to happen unless the file really is executable.
		 */
		if ((accmode & VEXEC) && ((dac_granted & VEXEC) == 0) &&
		    (file_mode & (S_IXUSR | S_IXGRP | S_IXOTH)) != 0 &&
		    !priv_check_cred(cred, PRIV_VFS_EXEC))
			priv_granted |= VEXEC;
	}

	if ((accmode & VREAD) && ((dac_granted & VREAD) == 0) &&
	    !priv_check_cred(cred, PRIV_VFS_READ))
		priv_granted |= VREAD;

	if ((accmode & VWRITE) && ((dac_granted & VWRITE) == 0) &&
	    !priv_check_cred(cred, PRIV_VFS_WRITE))
		priv_granted |= (VWRITE | VAPPEND);

	if ((accmode & VADMIN) && ((dac_granted & VADMIN) == 0) &&
	    !priv_check_cred(cred, PRIV_VFS_ADMIN))
		priv_granted |= VADMIN;

	if ((accmode & (priv_granted | dac_granted)) == accmode) {
		/* XXX audit: privilege used */
		if (privused != NULL)
			*privused = 1;
		return (0);
	}

	return ((accmode & VADMIN) ? EPERM : EACCES);
}