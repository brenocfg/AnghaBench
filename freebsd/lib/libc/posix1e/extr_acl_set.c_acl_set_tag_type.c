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
typedef  int acl_tag_t ;
typedef  TYPE_1__* acl_entry_t ;
struct TYPE_5__ {int ae_tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_BRAND_NFS4 ; 
 int /*<<< orphan*/  ACL_BRAND_POSIX ; 
#define  ACL_EVERYONE 134 
#define  ACL_GROUP 133 
#define  ACL_GROUP_OBJ 132 
#define  ACL_MASK 131 
#define  ACL_OTHER 130 
#define  ACL_USER 129 
#define  ACL_USER_OBJ 128 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  _entry_brand_as (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _entry_brand_may_be (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 

int
acl_set_tag_type(acl_entry_t entry_d, acl_tag_t tag_type)
{

	if (entry_d == NULL) {
		errno = EINVAL;
		return (-1);
	}

	switch(tag_type) {
	case ACL_OTHER:
	case ACL_MASK:
		if (!_entry_brand_may_be(entry_d, ACL_BRAND_POSIX)) {
			errno = EINVAL;
			return (-1);
		}
		_entry_brand_as(entry_d, ACL_BRAND_POSIX);
		break;
	case ACL_EVERYONE:
		if (!_entry_brand_may_be(entry_d, ACL_BRAND_NFS4)) {
			errno = EINVAL;
			return (-1);
		}
		_entry_brand_as(entry_d, ACL_BRAND_NFS4);
		break;
	}

	switch(tag_type) {
	case ACL_USER_OBJ:
	case ACL_USER:
	case ACL_GROUP_OBJ:
	case ACL_GROUP:
	case ACL_MASK:
	case ACL_OTHER:
	case ACL_EVERYONE:
		entry_d->ae_tag = tag_type;
		return (0);
	}

	errno = EINVAL;
	return (-1);
}