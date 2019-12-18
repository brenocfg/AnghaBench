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
struct acl_entry {int dummy; } ;
struct acl {int acl_cnt; int /*<<< orphan*/ * acl_entry; } ;
typedef  TYPE_1__* acl_t ;
struct TYPE_3__ {scalar_t__ ats_cur_entry; struct acl ats_acl; } ;

/* Variables and functions */
 int ACL_MAX_ENTRIES ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  errno ; 

int
acl_delete_entry_np(acl_t acl, int offset)
{
	struct acl *acl_int;
	int i;

	if (acl == NULL) {
		errno = EINVAL;
		return (-1);
	}

	acl_int = &acl->ats_acl;

	if (offset < 0 || offset >= acl_int->acl_cnt) {
		errno = EINVAL;
		return (-1);
	}

	if ((acl->ats_acl.acl_cnt < 1) ||
	    (acl->ats_acl.acl_cnt > ACL_MAX_ENTRIES)) {
		errno = EINVAL;
		return (-1);
	}

	/* ...shift the remaining entries... */
	for (i = offset; i < acl->ats_acl.acl_cnt - 1; ++i)
		acl->ats_acl.acl_entry[i] =
		    acl->ats_acl.acl_entry[i+1];
	/* ...drop the count and zero the unused entry... */
	acl->ats_acl.acl_cnt--;
	bzero(&acl->ats_acl.acl_entry[i],
	    sizeof(struct acl_entry));
	acl->ats_cur_entry = 0;

	return (0);
}