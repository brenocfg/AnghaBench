#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int acl_entry_type_t ;
typedef  TYPE_1__* acl_entry_t ;
struct TYPE_5__ {int ae_entry_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_BRAND_NFS4 ; 
#define  ACL_ENTRY_TYPE_ALARM 131 
#define  ACL_ENTRY_TYPE_ALLOW 130 
#define  ACL_ENTRY_TYPE_AUDIT 129 
#define  ACL_ENTRY_TYPE_DENY 128 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  _entry_brand_as (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _entry_brand_may_be (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 

int
acl_set_entry_type_np(acl_entry_t entry_d, acl_entry_type_t entry_type)
{

	if (entry_d == NULL) {
		errno = EINVAL;
		return (-1);
	}
	if (!_entry_brand_may_be(entry_d, ACL_BRAND_NFS4)) {
		errno = EINVAL;
		return (-1);
	}
	_entry_brand_as(entry_d, ACL_BRAND_NFS4);

	switch (entry_type) {
	case ACL_ENTRY_TYPE_ALLOW:
	case ACL_ENTRY_TYPE_DENY:
	case ACL_ENTRY_TYPE_AUDIT:
	case ACL_ENTRY_TYPE_ALARM:
		entry_d->ae_entry_type = entry_type;
		return (0);
	}

	errno = EINVAL;
	return (-1);
}