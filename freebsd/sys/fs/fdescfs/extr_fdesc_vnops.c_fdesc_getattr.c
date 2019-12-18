#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vop_getattr_args {struct vattr* a_vap; struct vnode* a_vp; } ;
struct vnode {int v_vflag; int /*<<< orphan*/  v_type; } ;
struct TYPE_3__ {scalar_t__ tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct vattr {int va_mode; int va_nlink; int /*<<< orphan*/  va_type; int /*<<< orphan*/  va_fileid; int /*<<< orphan*/  va_rdev; void* va_size; scalar_t__ va_filerev; scalar_t__ va_bytes; scalar_t__ va_flags; scalar_t__ va_gen; TYPE_1__ va_mtime; TYPE_1__ va_ctime; TYPE_1__ va_atime; void* va_blocksize; scalar_t__ va_gid; scalar_t__ va_uid; } ;
struct timeval {int /*<<< orphan*/  tv_sec; } ;
struct TYPE_4__ {int fd_type; int /*<<< orphan*/  fd_ix; } ;

/* Variables and functions */
 void* DEV_BSIZE ; 
#define  Fdesc 129 
#define  Froot 128 
 int /*<<< orphan*/  NODEV ; 
 int S_IRGRP ; 
 int S_IROTH ; 
 int S_IRUSR ; 
 int S_IXGRP ; 
 int S_IXOTH ; 
 int S_IXUSR ; 
 int /*<<< orphan*/  VCHR ; 
 int /*<<< orphan*/  VDIR ; 
 int /*<<< orphan*/  VLNK ; 
 TYPE_2__* VTOFDESC (struct vnode*) ; 
 int VV_READLINK ; 
 int /*<<< orphan*/  getboottime (struct timeval*) ; 
 int /*<<< orphan*/  makedev (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static int
fdesc_getattr(struct vop_getattr_args *ap)
{
	struct vnode *vp = ap->a_vp;
	struct vattr *vap = ap->a_vap;
	struct timeval boottime;

	getboottime(&boottime);
	vap->va_mode = S_IRUSR|S_IXUSR|S_IRGRP|S_IXGRP|S_IROTH|S_IXOTH;
	vap->va_fileid = VTOFDESC(vp)->fd_ix;
	vap->va_uid = 0;
	vap->va_gid = 0;
	vap->va_blocksize = DEV_BSIZE;
	vap->va_atime.tv_sec = boottime.tv_sec;
	vap->va_atime.tv_nsec = 0;
	vap->va_mtime = vap->va_atime;
	vap->va_ctime = vap->va_mtime;
	vap->va_gen = 0;
	vap->va_flags = 0;
	vap->va_bytes = 0;
	vap->va_filerev = 0;

	switch (VTOFDESC(vp)->fd_type) {
	case Froot:
		vap->va_type = VDIR;
		vap->va_nlink = 2;
		vap->va_size = DEV_BSIZE;
		vap->va_rdev = NODEV;
		break;

	case Fdesc:
		vap->va_type = (vp->v_vflag & VV_READLINK) == 0 ? VCHR : VLNK;
		vap->va_nlink = 1;
		vap->va_size = 0;
		vap->va_rdev = makedev(0, vap->va_fileid);
		break;

	default:
		panic("fdesc_getattr");
		break;
	}

	vp->v_type = vap->va_type;
	return (0);
}