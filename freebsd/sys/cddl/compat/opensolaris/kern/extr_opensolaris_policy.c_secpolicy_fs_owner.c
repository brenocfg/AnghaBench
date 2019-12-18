#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mount {TYPE_1__* mnt_cred; } ;
struct TYPE_5__ {scalar_t__ cr_uid; scalar_t__ cr_prison; } ;
typedef  TYPE_2__ cred_t ;
struct TYPE_4__ {scalar_t__ cr_uid; scalar_t__ cr_prison; } ;

/* Variables and functions */
 int EPERM ; 
 scalar_t__ zfs_super_owner ; 

int
secpolicy_fs_owner(struct mount *mp, cred_t *cr)
{

	if (zfs_super_owner) {
		if (cr->cr_uid == mp->mnt_cred->cr_uid &&
		    cr->cr_prison == mp->mnt_cred->cr_prison) {
			return (0);
		}
	}
	return (EPERM);
}