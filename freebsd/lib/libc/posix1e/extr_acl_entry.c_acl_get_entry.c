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
struct acl {int /*<<< orphan*/ * acl_entry; int /*<<< orphan*/  acl_cnt; } ;
typedef  TYPE_1__* acl_t ;
typedef  int /*<<< orphan*/ * acl_entry_t ;
struct TYPE_3__ {int /*<<< orphan*/  ats_cur_entry; struct acl ats_acl; } ;

/* Variables and functions */
#define  ACL_FIRST_ENTRY 129 
#define  ACL_NEXT_ENTRY 128 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  errno ; 

int
acl_get_entry(acl_t acl, int entry_id, acl_entry_t *entry_p)
{
	struct acl *acl_int;

	if (acl == NULL) {
		errno = EINVAL;
		return (-1);
	}
	acl_int = &acl->ats_acl;

	switch(entry_id) {
	case ACL_FIRST_ENTRY:
		acl->ats_cur_entry = 0;
		/* PASSTHROUGH */
	case ACL_NEXT_ENTRY:
		if (acl->ats_cur_entry >= acl->ats_acl.acl_cnt)
			return 0;
		*entry_p = &acl_int->acl_entry[acl->ats_cur_entry++];
		return (1);
	}

	errno = EINVAL;
	return (-1);
}