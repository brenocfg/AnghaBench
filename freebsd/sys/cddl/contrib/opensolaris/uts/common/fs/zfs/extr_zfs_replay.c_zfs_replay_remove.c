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
typedef  int /*<<< orphan*/  znode_t ;
typedef  int /*<<< orphan*/  zfsvfs_t ;
typedef  int /*<<< orphan*/  vnode_t ;
struct componentname {char* cn_nameptr; int cn_flags; int cn_lkflags; int /*<<< orphan*/  cn_thread; int /*<<< orphan*/  cn_cred; int /*<<< orphan*/  cn_nameiop; int /*<<< orphan*/  cn_namelen; } ;
struct TYPE_4__ {int lrc_txtype; } ;
struct TYPE_5__ {TYPE_1__ lr_common; int /*<<< orphan*/  lr_doid; } ;
typedef  TYPE_2__ lr_remove_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELETE ; 
 int /*<<< orphan*/  ENOTSUP ; 
 int FIGNORECASE ; 
 int ISLASTCN ; 
 int LK_EXCLUSIVE ; 
 int LK_RETRY ; 
 int SAVENAME ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int TX_CI ; 
#define  TX_REMOVE 129 
#define  TX_RMDIR 128 
 int /*<<< orphan*/  VN_RELE (int /*<<< orphan*/ ) ; 
 int VOP_LOOKUP (int /*<<< orphan*/ ,int /*<<< orphan*/ **,struct componentname*) ; 
 int VOP_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct componentname*) ; 
 int VOP_RMDIR (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct componentname*) ; 
 int /*<<< orphan*/  VOP_UNLOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZTOV (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  byteswap_uint64_array (TYPE_2__*,int) ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  kcred ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  vn_lock (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vput (int /*<<< orphan*/ *) ; 
 int zfs_zget (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int
zfs_replay_remove(void *arg1, void *arg2, boolean_t byteswap)
{
	zfsvfs_t *zfsvfs = arg1;
	lr_remove_t *lr = arg2;
	char *name = (char *)(lr + 1);	/* name follows lr_remove_t */
	znode_t *dzp;
	struct componentname cn;
	vnode_t *vp;
	int error;
	int vflg = 0;

	if (byteswap)
		byteswap_uint64_array(lr, sizeof (*lr));

	if ((error = zfs_zget(zfsvfs, lr->lr_doid, &dzp)) != 0)
		return (error);

	if (lr->lr_common.lrc_txtype & TX_CI)
		vflg |= FIGNORECASE;
	cn.cn_nameptr = name;
	cn.cn_namelen = strlen(name);
	cn.cn_nameiop = DELETE;
	cn.cn_flags = ISLASTCN | SAVENAME;
	cn.cn_lkflags = LK_EXCLUSIVE | LK_RETRY;
	cn.cn_cred = kcred;
	cn.cn_thread = curthread;
	vn_lock(ZTOV(dzp), LK_EXCLUSIVE | LK_RETRY);
	error = VOP_LOOKUP(ZTOV(dzp), &vp, &cn);
	if (error != 0) {
		VOP_UNLOCK(ZTOV(dzp), 0);
		goto fail;
	}

	switch ((int)lr->lr_common.lrc_txtype) {
	case TX_REMOVE:
		error = VOP_REMOVE(ZTOV(dzp), vp, &cn /*,vflg*/);
		break;
	case TX_RMDIR:
		error = VOP_RMDIR(ZTOV(dzp), vp, &cn /*,vflg*/);
		break;
	default:
		error = SET_ERROR(ENOTSUP);
	}
	vput(vp);
	VOP_UNLOCK(ZTOV(dzp), 0);

fail:
	VN_RELE(ZTOV(dzp));

	return (error);
}