#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mode_t ;
typedef  TYPE_1__* acl_t ;
struct TYPE_6__ {int /*<<< orphan*/  ats_acl; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_BRAND_NFS4 ; 
 int /*<<< orphan*/  ACL_MAX_ENTRIES ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  _acl_brand_as (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* acl_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acl_nfs4_sync_mode_from_acl (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acl_nfs4_trivial_from_mode_libc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  errno ; 

__attribute__((used)) static acl_t
_nfs4_acl_strip_np(const acl_t aclp, int canonical_six)
{
	acl_t newacl;
	mode_t mode = 0;

	newacl = acl_init(ACL_MAX_ENTRIES);
	if (newacl == NULL) {
		errno = ENOMEM;
		return (NULL);
	}

	_acl_brand_as(newacl, ACL_BRAND_NFS4);

	acl_nfs4_sync_mode_from_acl(&mode, &(aclp->ats_acl));
	acl_nfs4_trivial_from_mode_libc(&(newacl->ats_acl), mode, canonical_six);

	return (newacl);
}