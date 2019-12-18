#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  znode_t ;
typedef  int /*<<< orphan*/  zfsvfs_t ;
struct TYPE_6__ {int vsa_mask; int vsa_aclcnt; int vsa_aclentsz; int /*<<< orphan*/ * vsa_aclentp; scalar_t__ vsa_aclflags; } ;
typedef  TYPE_1__ vsecattr_t ;
typedef  int /*<<< orphan*/  vsa ;
typedef  int /*<<< orphan*/  vnode_t ;
struct TYPE_7__ {int lr_aclcnt; int /*<<< orphan*/  lr_foid; } ;
typedef  TYPE_2__ lr_acl_v0_t ;
typedef  scalar_t__ boolean_t ;
typedef  int /*<<< orphan*/  ace_t ;

/* Variables and functions */
 int LK_EXCLUSIVE ; 
 int LK_RETRY ; 
 int /*<<< orphan*/  VN_RELE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VOP_UNLOCK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int VSA_ACE ; 
 int VSA_ACECNT ; 
 int /*<<< orphan*/ * ZTOV (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  byteswap_uint64_array (TYPE_2__*,int) ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  kcred ; 
 int /*<<< orphan*/  vn_lock (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zfs_oldace_byteswap (int /*<<< orphan*/ *,int) ; 
 int zfs_setsecattr (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int zfs_zget (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int
zfs_replay_acl_v0(void *arg1, void *arg2, boolean_t byteswap)
{
	zfsvfs_t *zfsvfs = arg1;
	lr_acl_v0_t *lr = arg2;
	ace_t *ace = (ace_t *)(lr + 1);	/* ace array follows lr_acl_t */
	vsecattr_t vsa;
	vnode_t *vp;
	znode_t *zp;
	int error;

	if (byteswap) {
		byteswap_uint64_array(lr, sizeof (*lr));
		zfs_oldace_byteswap(ace, lr->lr_aclcnt);
	}

	if ((error = zfs_zget(zfsvfs, lr->lr_foid, &zp)) != 0)
		return (error);

	bzero(&vsa, sizeof (vsa));
	vsa.vsa_mask = VSA_ACE | VSA_ACECNT;
	vsa.vsa_aclcnt = lr->lr_aclcnt;
	vsa.vsa_aclentsz = sizeof (ace_t) * vsa.vsa_aclcnt;
	vsa.vsa_aclflags = 0;
	vsa.vsa_aclentp = ace;

	vp = ZTOV(zp);
	vn_lock(vp, LK_EXCLUSIVE | LK_RETRY);
	error = zfs_setsecattr(vp, &vsa, 0, kcred, NULL);
	VOP_UNLOCK(vp, 0);

	VN_RELE(vp);

	return (error);
}