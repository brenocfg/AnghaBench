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
typedef  int /*<<< orphan*/  acl_type_t ;
typedef  int /*<<< orphan*/  acl_t ;

/* Variables and functions */
#define  ACL_BRAND_NFS4 130 
#define  ACL_BRAND_POSIX 129 
#define  ACL_BRAND_UNKNOWN 128 
 int /*<<< orphan*/  ACL_TYPE_ACCESS ; 
 int /*<<< orphan*/  ACL_TYPE_DEFAULT ; 
 int /*<<< orphan*/  ACL_TYPE_NFS4 ; 
 int _acl_brand (int /*<<< orphan*/  const) ; 

int
_acl_type_not_valid_for_acl(const acl_t acl, acl_type_t type)
{

	switch (_acl_brand(acl)) {
	case ACL_BRAND_NFS4:
		if (type == ACL_TYPE_NFS4)
			return (0);
		break;

	case ACL_BRAND_POSIX:
		if (type == ACL_TYPE_ACCESS || type == ACL_TYPE_DEFAULT)
			return (0);
		break;

	case ACL_BRAND_UNKNOWN:
		return (0);
	}

	return (-1);
}