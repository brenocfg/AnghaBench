#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vnstat {int /*<<< orphan*/  vn_size; int /*<<< orphan*/  vn_fileid; scalar_t__ vn_mode; int /*<<< orphan*/  vn_fsid; } ;
struct vnode {int dummy; } ;
struct TYPE_2__ {scalar_t__ iso_mode; } ;
struct iso_node {int /*<<< orphan*/  i_size; int /*<<< orphan*/  i_number; TYPE_1__ inode; int /*<<< orphan*/  im_dev; scalar_t__ i_mnt; } ;
struct iso_mnt {int /*<<< orphan*/  i_size; int /*<<< orphan*/  i_number; TYPE_1__ inode; int /*<<< orphan*/  im_dev; scalar_t__ i_mnt; } ;
typedef  scalar_t__ mode_t ;
typedef  int /*<<< orphan*/  mnt ;
typedef  int /*<<< orphan*/  kvm_t ;
typedef  int /*<<< orphan*/  isonode ;

/* Variables and functions */
 scalar_t__ VTOI (struct vnode*) ; 
 int /*<<< orphan*/  dev2udev (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_read_all (int /*<<< orphan*/ *,unsigned long,struct iso_node*,int) ; 
 int /*<<< orphan*/  warnx (char*,void*) ; 

int
isofs_filestat(kvm_t *kd, struct vnode *vp, struct vnstat *vn)
{
	struct iso_node isonode;
	struct iso_mnt mnt;

	if (!kvm_read_all(kd, (unsigned long)VTOI(vp), &isonode,
	    sizeof(isonode))) {
		warnx("can't read iso_node at %p",
		    (void *)VTOI(vp));
		return (1);
	}
	if (!kvm_read_all(kd, (unsigned long)isonode.i_mnt, &mnt,
	    sizeof(mnt))) {
		warnx("can't read iso_mnt at %p",
		    (void *)VTOI(vp));
		return (1);
	}
	vn->vn_fsid = dev2udev(kd, mnt.im_dev);
	vn->vn_mode = (mode_t)isonode.inode.iso_mode;
	vn->vn_fileid = isonode.i_number;
	vn->vn_size = isonode.i_size;
	return (0);
}