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
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/ * acl_t ;

/* Variables and functions */
#define  ACL_BRAND_NFS4 129 
#define  ACL_BRAND_POSIX 128 
 int /*<<< orphan*/  EINVAL ; 
 int _acl_brand (int /*<<< orphan*/ *) ; 
 char* _nfs4_acl_to_text_np (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 char* _posix1e_acl_to_text (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  errno ; 

char *
acl_to_text_np(acl_t acl, ssize_t *len_p, int flags)
{

	if (acl == NULL) {
		errno = EINVAL;
		return(NULL);
	}

	switch (_acl_brand(acl)) {
	case ACL_BRAND_POSIX:
		return (_posix1e_acl_to_text(acl, len_p, flags));
	case ACL_BRAND_NFS4:
		return (_nfs4_acl_to_text_np(acl, len_p, flags));
	default:
		errno = EINVAL;
		return (NULL);
	}
}