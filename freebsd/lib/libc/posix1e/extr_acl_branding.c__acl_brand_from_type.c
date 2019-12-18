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
typedef  int acl_type_t ;
typedef  int /*<<< orphan*/  acl_t ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_BRAND_NFS4 ; 
 int /*<<< orphan*/  ACL_BRAND_POSIX ; 
#define  ACL_TYPE_ACCESS 130 
#define  ACL_TYPE_DEFAULT 129 
#define  ACL_TYPE_NFS4 128 
 int /*<<< orphan*/  _acl_brand_as (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
_acl_brand_from_type(acl_t acl, acl_type_t type)
{

	switch (type) {
	case ACL_TYPE_NFS4:
		_acl_brand_as(acl, ACL_BRAND_NFS4);
		break;
	case ACL_TYPE_ACCESS:
	case ACL_TYPE_DEFAULT:
		_acl_brand_as(acl, ACL_BRAND_POSIX);
		break;
	default:
		/* XXX: What to do here? */
		break;
	}
}