#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct acl_entry {int dummy; } ;
struct acl {int acl_cnt; int /*<<< orphan*/ * acl_entry; } ;
typedef  TYPE_1__* acl_t ;
typedef  struct acl_entry* acl_entry_t ;
struct TYPE_4__ {scalar_t__ ats_cur_entry; struct acl ats_acl; } ;

/* Variables and functions */
 int ACL_MAX_ENTRIES ; 
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ _acl_brand (TYPE_1__*) ; 
 scalar_t__ _entry_brand (struct acl_entry*) ; 
 scalar_t__ _entry_matches (int /*<<< orphan*/ *,struct acl_entry*) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  errno ; 

int
acl_delete_entry(acl_t acl, acl_entry_t entry_d)
{
	struct acl *acl_int;
	struct acl_entry entry_int;
	int i, j, found = 0;

	if (acl == NULL || entry_d == NULL) {
		errno = EINVAL;
		return (-1);
	}

	acl_int = &acl->ats_acl;

	if (_entry_brand(entry_d) != _acl_brand(acl)) {
		errno = EINVAL;
		return (-1);
	}

	if ((acl->ats_acl.acl_cnt < 1) ||
	    (acl->ats_acl.acl_cnt > ACL_MAX_ENTRIES)) {
		errno = EINVAL;
		return (-1);
	}

	/* Use a local copy to prevent deletion of more than this entry */
	entry_int = *entry_d;

	for (i = 0; i < acl->ats_acl.acl_cnt;) {
		if (_entry_matches(&(acl->ats_acl.acl_entry[i]), &entry_int)) {
			/* ...shift the remaining entries... */
			for (j = i; j < acl->ats_acl.acl_cnt - 1; ++j)
				acl->ats_acl.acl_entry[j] =
				    acl->ats_acl.acl_entry[j+1];
			/* ...drop the count and zero the unused entry... */
			acl->ats_acl.acl_cnt--;
			bzero(&acl->ats_acl.acl_entry[j],
			    sizeof(struct acl_entry));
			acl->ats_cur_entry = 0;
			
			/* Continue with the loop to remove all matching entries. */
			found = 1;
		} else
			i++;
	}

	if (found)
		return (0);

	errno = EINVAL;
	return (-1);
}