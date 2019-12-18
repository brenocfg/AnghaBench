#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct acl_entry {scalar_t__ ae_tag; int /*<<< orphan*/  ae_entry_type; void* ae_flags; void* ae_perm; int /*<<< orphan*/  ae_id; } ;
struct acl {int acl_maxcnt; int acl_cnt; struct acl_entry* acl_entry; } ;
struct TYPE_3__ {int a_flags; int a_access_mask; int a_type; int /*<<< orphan*/  a_who; } ;
typedef  TYPE_1__ ace_t ;

/* Variables and functions */
#define  ACE_ACCESS_ALLOWED_ACE_TYPE 131 
#define  ACE_ACCESS_DENIED_ACE_TYPE 130 
 int ACE_EVERYONE ; 
 int ACE_GROUP ; 
 int ACE_IDENTIFIER_GROUP ; 
 int ACE_OWNER ; 
#define  ACE_SYSTEM_ALARM_ACE_TYPE 129 
#define  ACE_SYSTEM_AUDIT_ACE_TYPE 128 
 int /*<<< orphan*/  ACL_ENTRY_TYPE_ALARM ; 
 int /*<<< orphan*/  ACL_ENTRY_TYPE_ALLOW ; 
 int /*<<< orphan*/  ACL_ENTRY_TYPE_AUDIT ; 
 int /*<<< orphan*/  ACL_ENTRY_TYPE_DENY ; 
 scalar_t__ ACL_EVERYONE ; 
 scalar_t__ ACL_GROUP ; 
 scalar_t__ ACL_GROUP_OBJ ; 
 int ACL_MAX_ENTRIES ; 
 int /*<<< orphan*/  ACL_UNDEFINED_ID ; 
 scalar_t__ ACL_USER ; 
 scalar_t__ ACL_USER_OBJ ; 
 int EINVAL ; 
 void* _bsd_from_zfs (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (struct acl*,int) ; 
 int /*<<< orphan*/  flags ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 int /*<<< orphan*/  perms ; 
 int /*<<< orphan*/  printf (char*) ; 

int
acl_from_aces(struct acl *aclp, const ace_t *aces, int nentries)
{
	int i;
	struct acl_entry *entry;
	const ace_t *ace;

	if (nentries < 1) {
		printf("acl_from_aces: empty ZFS ACL; returning EINVAL.\n");
		return (EINVAL);
	}

	if (nentries > ACL_MAX_ENTRIES) {
		/*
		 * I believe it may happen only when moving a pool
		 * from SunOS to FreeBSD.
		 */
		printf("acl_from_aces: ZFS ACL too big to fit "
		    "into 'struct acl'; returning EINVAL.\n");
		return (EINVAL);
	}

	bzero(aclp, sizeof(*aclp));
	aclp->acl_maxcnt = ACL_MAX_ENTRIES;
	aclp->acl_cnt = nentries;

	for (i = 0; i < nentries; i++) {
		entry = &(aclp->acl_entry[i]);
		ace = &(aces[i]);

		if (ace->a_flags & ACE_OWNER)
			entry->ae_tag = ACL_USER_OBJ;
		else if (ace->a_flags & ACE_GROUP)
			entry->ae_tag = ACL_GROUP_OBJ;
		else if (ace->a_flags & ACE_EVERYONE)
			entry->ae_tag = ACL_EVERYONE;
		else if (ace->a_flags & ACE_IDENTIFIER_GROUP)
			entry->ae_tag = ACL_GROUP;
		else
			entry->ae_tag = ACL_USER;

		if (entry->ae_tag == ACL_USER || entry->ae_tag == ACL_GROUP)
			entry->ae_id = ace->a_who;
		else
			entry->ae_id = ACL_UNDEFINED_ID;

		entry->ae_perm = _bsd_from_zfs(ace->a_access_mask, perms);
		entry->ae_flags = _bsd_from_zfs(ace->a_flags, flags);

		switch (ace->a_type) {
		case ACE_ACCESS_ALLOWED_ACE_TYPE:
			entry->ae_entry_type = ACL_ENTRY_TYPE_ALLOW;
			break;
		case ACE_ACCESS_DENIED_ACE_TYPE:
			entry->ae_entry_type = ACL_ENTRY_TYPE_DENY;
			break;
		case ACE_SYSTEM_AUDIT_ACE_TYPE:
			entry->ae_entry_type = ACL_ENTRY_TYPE_AUDIT;
			break;
		case ACE_SYSTEM_ALARM_ACE_TYPE:
			entry->ae_entry_type = ACL_ENTRY_TYPE_ALARM;
			break;
		default:
			panic("acl_from_aces: a_type is 0x%x", ace->a_type);
		}
	}

	return (0);
}