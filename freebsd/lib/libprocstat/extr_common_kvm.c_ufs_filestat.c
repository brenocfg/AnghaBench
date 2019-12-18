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
typedef  int /*<<< orphan*/  um ;
struct vnstat {int /*<<< orphan*/  vn_size; scalar_t__ vn_mode; int /*<<< orphan*/  vn_fileid; int /*<<< orphan*/  vn_fsid; } ;
struct vnode {int dummy; } ;
struct ufsmount {int /*<<< orphan*/  i_size; scalar_t__ i_mode; int /*<<< orphan*/  i_number; int /*<<< orphan*/  um_dev; scalar_t__ i_ump; } ;
struct inode {int /*<<< orphan*/  i_size; scalar_t__ i_mode; int /*<<< orphan*/  i_number; int /*<<< orphan*/  um_dev; scalar_t__ i_ump; } ;
typedef  scalar_t__ mode_t ;
typedef  int /*<<< orphan*/  kvm_t ;
typedef  int /*<<< orphan*/  inode ;

/* Variables and functions */
 scalar_t__ VTOI (struct vnode*) ; 
 int /*<<< orphan*/  dev2udev (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_read_all (int /*<<< orphan*/ *,unsigned long,struct ufsmount*,int) ; 
 int /*<<< orphan*/  warnx (char*,void*) ; 

int
ufs_filestat(kvm_t *kd, struct vnode *vp, struct vnstat *vn)
{
	struct inode inode;
	struct ufsmount um;

	if (!kvm_read_all(kd, (unsigned long)VTOI(vp), &inode, sizeof(inode))) {
		warnx("can't read inode at %p", (void *)VTOI(vp));
		return (1);
	}
	if (!kvm_read_all(kd, (unsigned long)inode.i_ump, &um, sizeof(um))) {
		warnx("can't read ufsmount at %p", (void *)inode.i_ump);
		return (1);
	}
	/*
	 * The st_dev from stat(2) is a dev_t. These kernel structures
	 * contain cdev pointers. We need to convert to dev_t to make
	 * comparisons
	 */
	vn->vn_fsid = dev2udev(kd, um.um_dev);
	vn->vn_fileid = inode.i_number;
	vn->vn_mode = (mode_t)inode.i_mode;
	vn->vn_size = inode.i_size;
	return (0);
}