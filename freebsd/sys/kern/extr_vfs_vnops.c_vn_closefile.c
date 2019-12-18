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
struct thread {int dummy; } ;
struct flock {int /*<<< orphan*/  l_type; scalar_t__ l_len; scalar_t__ l_start; int /*<<< orphan*/  l_whence; } ;
struct file {int f_flag; scalar_t__ f_type; int /*<<< orphan*/  f_cred; int /*<<< orphan*/ * f_ops; struct vnode* f_vnode; } ;

/* Variables and functions */
 scalar_t__ DTYPE_VNODE ; 
 int FHASLOCK ; 
 int /*<<< orphan*/  F_FLOCK ; 
 int /*<<< orphan*/  F_UNLCK ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  VOP_ADVLOCK (struct vnode*,struct file*,int /*<<< orphan*/ ,struct flock*,int /*<<< orphan*/ ) ; 
 scalar_t__ __predict_false (int) ; 
 int /*<<< orphan*/  badfileops ; 
 int vn_close1 (struct vnode*,int,int /*<<< orphan*/ ,struct thread*,int) ; 
 int /*<<< orphan*/  vrele (struct vnode*) ; 

__attribute__((used)) static int
vn_closefile(struct file *fp, struct thread *td)
{
	struct vnode *vp;
	struct flock lf;
	int error;
	bool ref;

	vp = fp->f_vnode;
	fp->f_ops = &badfileops;
	ref= (fp->f_flag & FHASLOCK) != 0 && fp->f_type == DTYPE_VNODE;

	error = vn_close1(vp, fp->f_flag, fp->f_cred, td, ref);

	if (__predict_false(ref)) {
		lf.l_whence = SEEK_SET;
		lf.l_start = 0;
		lf.l_len = 0;
		lf.l_type = F_UNLCK;
		(void) VOP_ADVLOCK(vp, fp, F_UNLCK, &lf, F_FLOCK);
		vrele(vp);
	}
	return (error);
}