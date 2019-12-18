#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct acl {int acl_cnt; TYPE_2__* acl_entry; } ;
typedef  TYPE_1__* acl_t ;
typedef  TYPE_2__* acl_entry_t ;
struct TYPE_6__ {scalar_t__ ae_flags; scalar_t__ ae_entry_type; int /*<<< orphan*/  ae_perm; int /*<<< orphan*/  ae_id; int /*<<< orphan*/  ae_tag; } ;
struct TYPE_5__ {scalar_t__ ats_cur_entry; struct acl ats_acl; } ;

/* Variables and functions */
 int ACL_MAX_ENTRIES ; 
 int /*<<< orphan*/  ACL_PERM_NONE ; 
 int /*<<< orphan*/  ACL_UNDEFINED_ID ; 
 int /*<<< orphan*/  ACL_UNDEFINED_TAG ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  errno ; 

int
acl_create_entry_np(acl_t *acl_p, acl_entry_t *entry_p, int offset)
{
	int i;
	struct acl *acl_int;

	if (acl_p == NULL) {
		errno = EINVAL;
		return (-1);
	}

	acl_int = &(*acl_p)->ats_acl;

	if (acl_int->acl_cnt + 1 >= ACL_MAX_ENTRIES) {
		errno = EINVAL;
		return (-1);
	}

	if (offset < 0 || offset > acl_int->acl_cnt) {
		errno = EINVAL;
		return (-1);
	}

	/* Make room for the new entry. */
	for (i = acl_int->acl_cnt; i > offset; i--)
		acl_int->acl_entry[i] = acl_int->acl_entry[i - 1];

	acl_int->acl_cnt++;

	*entry_p = &acl_int->acl_entry[offset];

	(**entry_p).ae_tag  = ACL_UNDEFINED_TAG;
	(**entry_p).ae_id   = ACL_UNDEFINED_ID;
	(**entry_p).ae_perm = ACL_PERM_NONE;
	(**entry_p).ae_entry_type = 0;
	(**entry_p).ae_flags= 0;

	(*acl_p)->ats_cur_entry = 0;

	return (0);
}