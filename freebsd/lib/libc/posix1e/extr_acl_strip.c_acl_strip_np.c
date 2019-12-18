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
typedef  int /*<<< orphan*/ * acl_t ;

/* Variables and functions */
#define  ACL_BRAND_NFS4 129 
#define  ACL_BRAND_POSIX 128 
 int /*<<< orphan*/  EINVAL ; 
 int _acl_brand (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/ * _nfs4_acl_strip_np (int /*<<< orphan*/ * const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * _posix1e_acl_strip_np (int /*<<< orphan*/ * const,int) ; 
 int /*<<< orphan*/  errno ; 

acl_t
acl_strip_np(const acl_t aclp, int recalculate_mask)
{
	switch (_acl_brand(aclp)) {
	case ACL_BRAND_NFS4:
		return (_nfs4_acl_strip_np(aclp, 0));

	case ACL_BRAND_POSIX:
		return (_posix1e_acl_strip_np(aclp, recalculate_mask));

	default:
		errno = EINVAL;
		return (NULL);
	}
}