#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vop_getattr_args {struct vattr* a_vap; struct vnode* a_vp; } ;
struct vnode {TYPE_3__* v_mount; int /*<<< orphan*/  v_type; } ;
struct vattr {int va_nlink; scalar_t__ va_filerev; scalar_t__ va_bytes; int /*<<< orphan*/  va_rdev; scalar_t__ va_flags; scalar_t__ va_gen; int /*<<< orphan*/  va_birthtime; int /*<<< orphan*/  va_ctime; int /*<<< orphan*/  va_mtime; int /*<<< orphan*/  va_atime; scalar_t__ va_size; int /*<<< orphan*/  va_blocksize; int /*<<< orphan*/  va_fileid; int /*<<< orphan*/  va_fsid; int /*<<< orphan*/  va_gid; int /*<<< orphan*/  va_uid; int /*<<< orphan*/  va_mode; int /*<<< orphan*/  va_type; } ;
struct mqfs_node {int /*<<< orphan*/  mn_birth; int /*<<< orphan*/  mn_ctime; int /*<<< orphan*/  mn_mtime; int /*<<< orphan*/  mn_atime; int /*<<< orphan*/  mn_fileno; int /*<<< orphan*/  mn_gid; int /*<<< orphan*/  mn_uid; int /*<<< orphan*/  mn_mode; } ;
struct TYPE_4__ {int /*<<< orphan*/ * val; } ;
struct TYPE_5__ {TYPE_1__ f_fsid; } ;
struct TYPE_6__ {TYPE_2__ mnt_stat; } ;

/* Variables and functions */
 int /*<<< orphan*/  NODEV ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct mqfs_node* VTON (struct vnode*) ; 

__attribute__((used)) static int
mqfs_getattr(struct vop_getattr_args *ap)
{
	struct vnode *vp = ap->a_vp;
	struct mqfs_node *pn = VTON(vp);
	struct vattr *vap = ap->a_vap;
	int error = 0;

	vap->va_type = vp->v_type;
	vap->va_mode = pn->mn_mode;
	vap->va_nlink = 1;
	vap->va_uid = pn->mn_uid;
	vap->va_gid = pn->mn_gid;
	vap->va_fsid = vp->v_mount->mnt_stat.f_fsid.val[0];
	vap->va_fileid = pn->mn_fileno;
	vap->va_size = 0;
	vap->va_blocksize = PAGE_SIZE;
	vap->va_bytes = vap->va_size = 0;
	vap->va_atime = pn->mn_atime;
	vap->va_mtime = pn->mn_mtime;
	vap->va_ctime = pn->mn_ctime;
	vap->va_birthtime = pn->mn_birth;
	vap->va_gen = 0;
	vap->va_flags = 0;
	vap->va_rdev = NODEV;
	vap->va_bytes = 0;
	vap->va_filerev = 0;
	return (error);
}