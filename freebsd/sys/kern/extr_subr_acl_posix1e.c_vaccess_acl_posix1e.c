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
typedef  int /*<<< orphan*/  uid_t ;
struct ucred {int /*<<< orphan*/  cr_uid; } ;
struct acl_entry {int ae_tag; int ae_perm; int /*<<< orphan*/  ae_id; } ;
struct acl {int acl_cnt; struct acl_entry* acl_entry; } ;
typedef  int /*<<< orphan*/  gid_t ;
typedef  enum vtype { ____Placeholder_vtype } vtype ;
typedef  int accmode_t ;

/* Variables and functions */
 int ACL_EXECUTE ; 
#define  ACL_GROUP 133 
#define  ACL_GROUP_OBJ 132 
#define  ACL_MASK 131 
#define  ACL_OTHER 130 
 int ACL_READ ; 
#define  ACL_USER 129 
#define  ACL_USER_OBJ 128 
 int ACL_WRITE ; 
 int EACCES ; 
 int EPERM ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  PRIV_VFS_ADMIN ; 
 int /*<<< orphan*/  PRIV_VFS_EXEC ; 
 int /*<<< orphan*/  PRIV_VFS_LOOKUP ; 
 int /*<<< orphan*/  PRIV_VFS_READ ; 
 int /*<<< orphan*/  PRIV_VFS_WRITE ; 
 int S_IXGRP ; 
 int S_IXOTH ; 
 int S_IXUSR ; 
 int VADMIN ; 
 int VAPPEND ; 
 int VDIR ; 
 int VEXEC ; 
 int VREAD ; 
 int VWRITE ; 
 int acl_posix1e_acl_to_mode (struct acl*) ; 
 int /*<<< orphan*/  groupmember (int /*<<< orphan*/ ,struct ucred*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  priv_check_cred (struct ucred*,int /*<<< orphan*/ ) ; 

int
vaccess_acl_posix1e(enum vtype type, uid_t file_uid, gid_t file_gid,
    struct acl *acl, accmode_t accmode, struct ucred *cred, int *privused)
{
	struct acl_entry *acl_other, *acl_mask;
	accmode_t dac_granted;
	accmode_t priv_granted;
	accmode_t acl_mask_granted;
	int group_matched, i;

	KASSERT((accmode & ~(VEXEC | VWRITE | VREAD | VADMIN | VAPPEND)) == 0,
	    ("invalid bit in accmode"));
	KASSERT((accmode & VAPPEND) == 0 || (accmode & VWRITE),
	    	("VAPPEND without VWRITE"));

	/*
	 * Look for a normal, non-privileged way to access the file/directory
	 * as requested.  If it exists, go with that.  Otherwise, attempt to
	 * use privileges granted via priv_granted.  In some cases, which
	 * privileges to use may be ambiguous due to "best match", in which
	 * case fall back on first match for the time being.
	 */
	if (privused != NULL)
		*privused = 0;

	/*
	 * Determine privileges now, but don't apply until we've found a DAC
	 * entry that matches but has failed to allow access.
	 *
	 * XXXRW: Ideally, we'd determine the privileges required before
	 * asking for them.
	 */
	priv_granted = 0;

	if (type == VDIR) {
		if ((accmode & VEXEC) && !priv_check_cred(cred, PRIV_VFS_LOOKUP))
			priv_granted |= VEXEC;
	} else {
		/*
		 * Ensure that at least one execute bit is on. Otherwise,
		 * a privileged user will always succeed, and we don't want
		 * this to happen unless the file really is executable.
		 */
		if ((accmode & VEXEC) && (acl_posix1e_acl_to_mode(acl) &
		    (S_IXUSR | S_IXGRP | S_IXOTH)) != 0 &&
		    !priv_check_cred(cred, PRIV_VFS_EXEC))
			priv_granted |= VEXEC;
	}

	if ((accmode & VREAD) && !priv_check_cred(cred, PRIV_VFS_READ))
		priv_granted |= VREAD;

	if (((accmode & VWRITE) || (accmode & VAPPEND)) &&
	    !priv_check_cred(cred, PRIV_VFS_WRITE))
		priv_granted |= (VWRITE | VAPPEND);

	if ((accmode & VADMIN) && !priv_check_cred(cred, PRIV_VFS_ADMIN))
		priv_granted |= VADMIN;

	/*
	 * The owner matches if the effective uid associated with the
	 * credential matches that of the ACL_USER_OBJ entry.  While we're
	 * doing the first scan, also cache the location of the ACL_MASK and
	 * ACL_OTHER entries, preventing some future iterations.
	 */
	acl_mask = acl_other = NULL;
	for (i = 0; i < acl->acl_cnt; i++) {
		switch (acl->acl_entry[i].ae_tag) {
		case ACL_USER_OBJ:
			if (file_uid != cred->cr_uid)
				break;
			dac_granted = 0;
			dac_granted |= VADMIN;
			if (acl->acl_entry[i].ae_perm & ACL_EXECUTE)
				dac_granted |= VEXEC;
			if (acl->acl_entry[i].ae_perm & ACL_READ)
				dac_granted |= VREAD;
			if (acl->acl_entry[i].ae_perm & ACL_WRITE)
				dac_granted |= (VWRITE | VAPPEND);
			if ((accmode & dac_granted) == accmode)
				return (0);

			/*
			 * XXXRW: Do privilege lookup here.
			 */
			if ((accmode & (dac_granted | priv_granted)) ==
			    accmode) {
				if (privused != NULL)
					*privused = 1;
				return (0);
			}
			goto error;

		case ACL_MASK:
			acl_mask = &acl->acl_entry[i];
			break;

		case ACL_OTHER:
			acl_other = &acl->acl_entry[i];
			break;

		default:
			break;
		}
	}

	/*
	 * An ACL_OTHER entry should always exist in a valid access ACL.  If
	 * it doesn't, then generate a serious failure.  For now, this means
	 * a debugging message and EPERM, but in the future should probably
	 * be a panic.
	 */
	if (acl_other == NULL) {
		/*
		 * XXX This should never happen
		 */
		printf("vaccess_acl_posix1e: ACL_OTHER missing\n");
		return (EPERM);
	}

	/*
	 * Checks against ACL_USER, ACL_GROUP_OBJ, and ACL_GROUP fields are
	 * masked by an ACL_MASK entry, if any.  As such, first identify the
	 * ACL_MASK field, then iterate through identifying potential user
	 * matches, then group matches.  If there is no ACL_MASK, assume that
	 * the mask allows all requests to succeed.
	 */
	if (acl_mask != NULL) {
		acl_mask_granted = 0;
		if (acl_mask->ae_perm & ACL_EXECUTE)
			acl_mask_granted |= VEXEC;
		if (acl_mask->ae_perm & ACL_READ)
			acl_mask_granted |= VREAD;
		if (acl_mask->ae_perm & ACL_WRITE)
			acl_mask_granted |= (VWRITE | VAPPEND);
	} else
		acl_mask_granted = VEXEC | VREAD | VWRITE | VAPPEND;

	/*
	 * Check ACL_USER ACL entries.  There will either be one or no
	 * matches; if there is one, we accept or rejected based on the
	 * match; otherwise, we continue on to groups.
	 */
	for (i = 0; i < acl->acl_cnt; i++) {
		switch (acl->acl_entry[i].ae_tag) {
		case ACL_USER:
			if (acl->acl_entry[i].ae_id != cred->cr_uid)
				break;
			dac_granted = 0;
			if (acl->acl_entry[i].ae_perm & ACL_EXECUTE)
				dac_granted |= VEXEC;
			if (acl->acl_entry[i].ae_perm & ACL_READ)
				dac_granted |= VREAD;
			if (acl->acl_entry[i].ae_perm & ACL_WRITE)
				dac_granted |= (VWRITE | VAPPEND);
			dac_granted &= acl_mask_granted;
			if ((accmode & dac_granted) == accmode)
				return (0);
			/*
			 * XXXRW: Do privilege lookup here.
			 */
			if ((accmode & (dac_granted | priv_granted)) !=
			    accmode)
				goto error;

			if (privused != NULL)
				*privused = 1;
			return (0);
		}
	}

	/*
	 * Group match is best-match, not first-match, so find a "best"
	 * match.  Iterate across, testing each potential group match.  Make
	 * sure we keep track of whether we found a match or not, so that we
	 * know if we should try again with any available privilege, or if we
	 * should move on to ACL_OTHER.
	 */
	group_matched = 0;
	for (i = 0; i < acl->acl_cnt; i++) {
		switch (acl->acl_entry[i].ae_tag) {
		case ACL_GROUP_OBJ:
			if (!groupmember(file_gid, cred))
				break;
			dac_granted = 0;
			if (acl->acl_entry[i].ae_perm & ACL_EXECUTE)
				dac_granted |= VEXEC;
			if (acl->acl_entry[i].ae_perm & ACL_READ)
				dac_granted |= VREAD;
			if (acl->acl_entry[i].ae_perm & ACL_WRITE)
				dac_granted |= (VWRITE | VAPPEND);
			dac_granted  &= acl_mask_granted;

			if ((accmode & dac_granted) == accmode)
				return (0);

			group_matched = 1;
			break;

		case ACL_GROUP:
			if (!groupmember(acl->acl_entry[i].ae_id, cred))
				break;
			dac_granted = 0;
			if (acl->acl_entry[i].ae_perm & ACL_EXECUTE)
				dac_granted |= VEXEC;
			if (acl->acl_entry[i].ae_perm & ACL_READ)
				dac_granted |= VREAD;
			if (acl->acl_entry[i].ae_perm & ACL_WRITE)
				dac_granted |= (VWRITE | VAPPEND);
			dac_granted  &= acl_mask_granted;

			if ((accmode & dac_granted) == accmode)
				return (0);

			group_matched = 1;
			break;

		default:
			break;
		}
	}

	if (group_matched == 1) {
		/*
		 * There was a match, but it did not grant rights via pure
		 * DAC.  Try again, this time with privilege.
		 */
		for (i = 0; i < acl->acl_cnt; i++) {
			switch (acl->acl_entry[i].ae_tag) {
			case ACL_GROUP_OBJ:
				if (!groupmember(file_gid, cred))
					break;
				dac_granted = 0;
				if (acl->acl_entry[i].ae_perm & ACL_EXECUTE)
					dac_granted |= VEXEC;
				if (acl->acl_entry[i].ae_perm & ACL_READ)
					dac_granted |= VREAD;
				if (acl->acl_entry[i].ae_perm & ACL_WRITE)
					dac_granted |= (VWRITE | VAPPEND);
				dac_granted &= acl_mask_granted;

				/*
				 * XXXRW: Do privilege lookup here.
				 */
				if ((accmode & (dac_granted | priv_granted))
				    != accmode)
					break;

				if (privused != NULL)
					*privused = 1;
				return (0);

			case ACL_GROUP:
				if (!groupmember(acl->acl_entry[i].ae_id,
				    cred))
					break;
				dac_granted = 0;
				if (acl->acl_entry[i].ae_perm & ACL_EXECUTE)
				dac_granted |= VEXEC;
				if (acl->acl_entry[i].ae_perm & ACL_READ)
					dac_granted |= VREAD;
				if (acl->acl_entry[i].ae_perm & ACL_WRITE)
					dac_granted |= (VWRITE | VAPPEND);
				dac_granted &= acl_mask_granted;

				/*
				 * XXXRW: Do privilege lookup here.
				 */
				if ((accmode & (dac_granted | priv_granted))
				    != accmode)
					break;

				if (privused != NULL)
					*privused = 1;
				return (0);

			default:
				break;
			}
		}
		/*
		 * Even with privilege, group membership was not sufficient.
		 * Return failure.
		 */
		goto error;
	}
		
	/*
	 * Fall back on ACL_OTHER.  ACL_MASK is not applied to ACL_OTHER.
	 */
	dac_granted = 0;
	if (acl_other->ae_perm & ACL_EXECUTE)
		dac_granted |= VEXEC;
	if (acl_other->ae_perm & ACL_READ)
		dac_granted |= VREAD;
	if (acl_other->ae_perm & ACL_WRITE)
		dac_granted |= (VWRITE | VAPPEND);

	if ((accmode & dac_granted) == accmode)
		return (0);
	/*
	 * XXXRW: Do privilege lookup here.
	 */
	if ((accmode & (dac_granted | priv_granted)) == accmode) {
		if (privused != NULL)
			*privused = 1;
		return (0);
	}

error:
	return ((accmode & VADMIN) ? EPERM : EACCES);
}