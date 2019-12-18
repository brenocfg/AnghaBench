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
struct acl {scalar_t__ acl_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  acl_nfs4_sync_acl_from_mode_draft (struct acl*,int,int) ; 
 int /*<<< orphan*/  acl_nfs4_trivial_from_mode (struct acl*,int) ; 

void
acl_nfs4_trivial_from_mode_libc(struct acl *aclp, int mode, int canonical_six)
{

	aclp->acl_cnt = 0;
	if (canonical_six)
		acl_nfs4_sync_acl_from_mode_draft(aclp, mode, -1);
	else
		acl_nfs4_trivial_from_mode(aclp, mode);
}