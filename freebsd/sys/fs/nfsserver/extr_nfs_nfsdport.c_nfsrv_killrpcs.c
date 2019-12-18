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
struct nfsmount {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  newnfs_nmcancelreqs (struct nfsmount*) ; 

void
nfsrv_killrpcs(struct nfsmount *nmp)
{

	/*
	 * Call newnfs_nmcancelreqs() to cause
	 * any RPCs in progress on the mount point to
	 * fail.
	 * This will cause any process waiting for an
	 * RPC to complete while holding a vnode lock
	 * on the mounted-on vnode (such as "df" or
	 * a non-forced "umount") to fail.
	 * This will unlock the mounted-on vnode so
	 * a forced dismount can succeed.
	 * The NFSMNTP_CANCELRPCS flag should be set when this function is
	 * called.
	 */
	newnfs_nmcancelreqs(nmp);
}