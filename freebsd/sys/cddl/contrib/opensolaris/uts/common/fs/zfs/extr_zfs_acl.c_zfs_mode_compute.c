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
typedef  int /*<<< orphan*/  zfs_acl_t ;
typedef  int /*<<< orphan*/  zfs_ace_hdr_t ;
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  scalar_t__ mode_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int ACE_EVERYONE ; 
 int ACE_EXECUTE ; 
 int ACE_IDENTIFIER_GROUP ; 
 int ACE_INHERIT_ONLY_ACE ; 
 int ACE_OWNER ; 
 int ACE_READ_DATA ; 
 int ACE_TYPE_FLAGS ; 
 int ACE_WRITE_DATA ; 
 int ALLOW ; 
 scalar_t__ ALL_MODE_EXECS ; 
 scalar_t__ B_FALSE ; 
 scalar_t__ B_TRUE ; 
 int DENY ; 
 int OWNING_GROUP ; 
 scalar_t__ S_IFMT ; 
 scalar_t__ S_IRGRP ; 
 scalar_t__ S_IROTH ; 
 scalar_t__ S_IRUSR ; 
 scalar_t__ S_ISGID ; 
 scalar_t__ S_ISUID ; 
 scalar_t__ S_ISVTX ; 
 scalar_t__ S_IWGRP ; 
 scalar_t__ S_IWOTH ; 
 scalar_t__ S_IWUSR ; 
 scalar_t__ S_IXGRP ; 
 scalar_t__ S_IXOTH ; 
 scalar_t__ S_IXUSR ; 
 scalar_t__ ZFS_NO_EXECS_DENIED ; 
 int /*<<< orphan*/ * zfs_acl_next_ace (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,int*,int*,int*) ; 
 int /*<<< orphan*/  zfs_acl_valid_ace_type (int,int) ; 

uint64_t
zfs_mode_compute(uint64_t fmode, zfs_acl_t *aclp,
    uint64_t *pflags, uint64_t fuid, uint64_t fgid)
{
	int		entry_type;
	mode_t		mode;
	mode_t		seen = 0;
	zfs_ace_hdr_t	*acep = NULL;
	uint64_t	who;
	uint16_t	iflags, type;
	uint32_t	access_mask;
	boolean_t	an_exec_denied = B_FALSE;

	mode = (fmode & (S_IFMT | S_ISUID | S_ISGID | S_ISVTX));

	while (acep = zfs_acl_next_ace(aclp, acep, &who,
	    &access_mask, &iflags, &type)) {

		if (!zfs_acl_valid_ace_type(type, iflags))
			continue;

		entry_type = (iflags & ACE_TYPE_FLAGS);

		/*
		 * Skip over any inherit_only ACEs
		 */
		if (iflags & ACE_INHERIT_ONLY_ACE)
			continue;

		if (entry_type == ACE_OWNER || (entry_type == 0 &&
		    who == fuid)) {
			if ((access_mask & ACE_READ_DATA) &&
			    (!(seen & S_IRUSR))) {
				seen |= S_IRUSR;
				if (type == ALLOW) {
					mode |= S_IRUSR;
				}
			}
			if ((access_mask & ACE_WRITE_DATA) &&
			    (!(seen & S_IWUSR))) {
				seen |= S_IWUSR;
				if (type == ALLOW) {
					mode |= S_IWUSR;
				}
			}
			if ((access_mask & ACE_EXECUTE) &&
			    (!(seen & S_IXUSR))) {
				seen |= S_IXUSR;
				if (type == ALLOW) {
					mode |= S_IXUSR;
				}
			}
		} else if (entry_type == OWNING_GROUP ||
		    (entry_type == ACE_IDENTIFIER_GROUP && who == fgid)) {
			if ((access_mask & ACE_READ_DATA) &&
			    (!(seen & S_IRGRP))) {
				seen |= S_IRGRP;
				if (type == ALLOW) {
					mode |= S_IRGRP;
				}
			}
			if ((access_mask & ACE_WRITE_DATA) &&
			    (!(seen & S_IWGRP))) {
				seen |= S_IWGRP;
				if (type == ALLOW) {
					mode |= S_IWGRP;
				}
			}
			if ((access_mask & ACE_EXECUTE) &&
			    (!(seen & S_IXGRP))) {
				seen |= S_IXGRP;
				if (type == ALLOW) {
					mode |= S_IXGRP;
				}
			}
		} else if (entry_type == ACE_EVERYONE) {
			if ((access_mask & ACE_READ_DATA)) {
				if (!(seen & S_IRUSR)) {
					seen |= S_IRUSR;
					if (type == ALLOW) {
						mode |= S_IRUSR;
					}
				}
				if (!(seen & S_IRGRP)) {
					seen |= S_IRGRP;
					if (type == ALLOW) {
						mode |= S_IRGRP;
					}
				}
				if (!(seen & S_IROTH)) {
					seen |= S_IROTH;
					if (type == ALLOW) {
						mode |= S_IROTH;
					}
				}
			}
			if ((access_mask & ACE_WRITE_DATA)) {
				if (!(seen & S_IWUSR)) {
					seen |= S_IWUSR;
					if (type == ALLOW) {
						mode |= S_IWUSR;
					}
				}
				if (!(seen & S_IWGRP)) {
					seen |= S_IWGRP;
					if (type == ALLOW) {
						mode |= S_IWGRP;
					}
				}
				if (!(seen & S_IWOTH)) {
					seen |= S_IWOTH;
					if (type == ALLOW) {
						mode |= S_IWOTH;
					}
				}
			}
			if ((access_mask & ACE_EXECUTE)) {
				if (!(seen & S_IXUSR)) {
					seen |= S_IXUSR;
					if (type == ALLOW) {
						mode |= S_IXUSR;
					}
				}
				if (!(seen & S_IXGRP)) {
					seen |= S_IXGRP;
					if (type == ALLOW) {
						mode |= S_IXGRP;
					}
				}
				if (!(seen & S_IXOTH)) {
					seen |= S_IXOTH;
					if (type == ALLOW) {
						mode |= S_IXOTH;
					}
				}
			}
		} else {
			/*
			 * Only care if this IDENTIFIER_GROUP or
			 * USER ACE denies execute access to someone,
			 * mode is not affected
			 */
			if ((access_mask & ACE_EXECUTE) && type == DENY)
				an_exec_denied = B_TRUE;
		}
	}

	/*
	 * Failure to allow is effectively a deny, so execute permission
	 * is denied if it was never mentioned or if we explicitly
	 * weren't allowed it.
	 */
	if (!an_exec_denied &&
	    ((seen & ALL_MODE_EXECS) != ALL_MODE_EXECS ||
	    (mode & ALL_MODE_EXECS) != ALL_MODE_EXECS))
		an_exec_denied = B_TRUE;

	if (an_exec_denied)
		*pflags &= ~ZFS_NO_EXECS_DENIED;
	else
		*pflags |= ZFS_NO_EXECS_DENIED;

	return (mode);
}