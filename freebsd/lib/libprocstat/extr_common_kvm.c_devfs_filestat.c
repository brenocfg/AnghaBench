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
struct vnstat {int vn_mode; scalar_t__ vn_size; int /*<<< orphan*/  vn_fileid; int /*<<< orphan*/  vn_fsid; } ;
struct vnode {scalar_t__ v_data; } ;
struct TYPE_3__ {int /*<<< orphan*/ * val; } ;
struct TYPE_4__ {TYPE_1__ f_fsid; } ;
struct mount {int de_mode; int /*<<< orphan*/  de_inode; TYPE_2__ mnt_stat; } ;
struct devfs_dirent {int de_mode; int /*<<< orphan*/  de_inode; TYPE_2__ mnt_stat; } ;
typedef  int /*<<< orphan*/  mount ;
typedef  int /*<<< orphan*/  kvm_t ;
typedef  int /*<<< orphan*/  devfs_dirent ;

/* Variables and functions */
 int S_IFCHR ; 
 int S_IFMT ; 
 scalar_t__ getvnodedata (struct vnode*) ; 
 scalar_t__ getvnodemount (struct vnode*) ; 
 int /*<<< orphan*/  kvm_read_all (int /*<<< orphan*/ *,unsigned long,struct mount*,int) ; 
 int /*<<< orphan*/  warnx (char*,void*) ; 

int
devfs_filestat(kvm_t *kd, struct vnode *vp, struct vnstat *vn)
{
	struct devfs_dirent devfs_dirent;
	struct mount mount;

	if (!kvm_read_all(kd, (unsigned long)getvnodedata(vp), &devfs_dirent,
	    sizeof(devfs_dirent))) {
		warnx("can't read devfs_dirent at %p",
		    (void *)vp->v_data);
		return (1);
	}
	if (!kvm_read_all(kd, (unsigned long)getvnodemount(vp), &mount,
	    sizeof(mount))) {
		warnx("can't read mount at %p",
		    (void *)getvnodemount(vp));
		return (1);
	}
	vn->vn_fsid = mount.mnt_stat.f_fsid.val[0];
	vn->vn_fileid = devfs_dirent.de_inode;
	vn->vn_mode = (devfs_dirent.de_mode & ~S_IFMT) | S_IFCHR;
	vn->vn_size = 0;
	return (0);
}