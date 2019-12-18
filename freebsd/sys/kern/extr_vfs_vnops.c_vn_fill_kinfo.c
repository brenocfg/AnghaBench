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
struct vnode {int dummy; } ;
struct kinfo_file {int /*<<< orphan*/  kf_type; } ;
struct filedesc {int dummy; } ;
struct file {scalar_t__ f_type; struct vnode* f_vnode; } ;

/* Variables and functions */
 scalar_t__ DTYPE_FIFO ; 
 int /*<<< orphan*/  FILEDESC_SLOCK (struct filedesc*) ; 
 int /*<<< orphan*/  FILEDESC_SUNLOCK (struct filedesc*) ; 
 int /*<<< orphan*/  KF_TYPE_FIFO ; 
 int /*<<< orphan*/  KF_TYPE_VNODE ; 
 int vn_fill_kinfo_vnode (struct vnode*,struct kinfo_file*) ; 
 int /*<<< orphan*/  vref (struct vnode*) ; 
 int /*<<< orphan*/  vrele (struct vnode*) ; 

int
vn_fill_kinfo(struct file *fp, struct kinfo_file *kif, struct filedesc *fdp)
{
	struct vnode *vp;
	int error;

	if (fp->f_type == DTYPE_FIFO)
		kif->kf_type = KF_TYPE_FIFO;
	else
		kif->kf_type = KF_TYPE_VNODE;
	vp = fp->f_vnode;
	vref(vp);
	FILEDESC_SUNLOCK(fdp);
	error = vn_fill_kinfo_vnode(vp, kif);
	vrele(vp);
	FILEDESC_SLOCK(fdp);
	return (error);
}