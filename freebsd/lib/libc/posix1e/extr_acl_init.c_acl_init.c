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
struct acl_t_struct {int dummy; } ;
typedef  TYPE_2__* acl_t ;
struct TYPE_5__ {int acl_maxcnt; } ;
struct TYPE_6__ {TYPE_1__ ats_acl; int /*<<< orphan*/  ats_brand; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_BRAND_UNKNOWN ; 
 int ACL_MAX_ENTRIES ; 
 int EINVAL ; 
 int ENOMEM ; 
 int _ACL_T_ALIGNMENT_BITS ; 
 int /*<<< orphan*/  bzero (TYPE_2__*,int) ; 
 int errno ; 
 int posix_memalign (void*,int,int) ; 

acl_t
acl_init(int count)
{
	int error;
	acl_t acl;

	if (count > ACL_MAX_ENTRIES) {
		errno = ENOMEM;
		return (NULL);
	}
	if (count < 0) {
		errno = EINVAL;
		return (NULL);
	}

	error = posix_memalign((void *)&acl, 1 << _ACL_T_ALIGNMENT_BITS,
	    sizeof(struct acl_t_struct));
	if (error) {
		errno = error;
		return (NULL);
	}

	bzero(acl, sizeof(struct acl_t_struct));
	acl->ats_brand = ACL_BRAND_UNKNOWN;
	acl->ats_acl.acl_maxcnt = ACL_MAX_ENTRIES;

	return (acl);
}