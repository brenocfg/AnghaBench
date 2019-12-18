#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vnode {TYPE_2__* v_mount; } ;
struct thread {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  fh_fid; int /*<<< orphan*/  fh_fsid; } ;
typedef  TYPE_3__ fhandle_t ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_5__ {int /*<<< orphan*/  f_fsid; } ;
struct TYPE_6__ {TYPE_1__ mnt_stat; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFSBZERO (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NFSEXITCODE (int) ; 
 int VOP_VPTOFH (struct vnode*,int /*<<< orphan*/ *) ; 

int
nfsvno_getfh(struct vnode *vp, fhandle_t *fhp, struct thread *p)
{
	int error;

	NFSBZERO((caddr_t)fhp, sizeof(fhandle_t));
	fhp->fh_fsid = vp->v_mount->mnt_stat.f_fsid;
	error = VOP_VPTOFH(vp, &fhp->fh_fid);

	NFSEXITCODE(error);
	return (error);
}