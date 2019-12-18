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
struct undelete_args {int /*<<< orphan*/  path; } ;
struct thread {int dummy; } ;
struct TYPE_2__ {int cn_flags; } ;
struct nameidata {scalar_t__ ni_vp; scalar_t__ ni_dvp; TYPE_1__ ni_cnd; } ;
struct mount {int dummy; } ;

/* Variables and functions */
 int AUDITVNODE1 ; 
 int /*<<< orphan*/  DELETE ; 
 int DOWHITEOUT ; 
 int EEXIST ; 
 int ISWHITEOUT ; 
 int LOCKPARENT ; 
 int /*<<< orphan*/  NDFREE (struct nameidata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NDF_ONLY_PNBUF ; 
 int /*<<< orphan*/  NDINIT (struct nameidata*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct thread*) ; 
 scalar_t__ NULLVP ; 
 int PCATCH ; 
 int /*<<< orphan*/  UIO_USERSPACE ; 
 int VOP_WHITEOUT (scalar_t__,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int V_NOWAIT ; 
 int V_XSLEEP ; 
 int /*<<< orphan*/  bwillwrite () ; 
 int namei (struct nameidata*) ; 
 int /*<<< orphan*/  vn_finished_write (struct mount*) ; 
 int vn_start_write (int /*<<< orphan*/ *,struct mount**,int) ; 
 int /*<<< orphan*/  vput (scalar_t__) ; 
 int /*<<< orphan*/  vrele (scalar_t__) ; 

int
sys_undelete(struct thread *td, struct undelete_args *uap)
{
	struct mount *mp;
	struct nameidata nd;
	int error;

restart:
	bwillwrite();
	NDINIT(&nd, DELETE, LOCKPARENT | DOWHITEOUT | AUDITVNODE1,
	    UIO_USERSPACE, uap->path, td);
	error = namei(&nd);
	if (error != 0)
		return (error);

	if (nd.ni_vp != NULLVP || !(nd.ni_cnd.cn_flags & ISWHITEOUT)) {
		NDFREE(&nd, NDF_ONLY_PNBUF);
		if (nd.ni_vp == nd.ni_dvp)
			vrele(nd.ni_dvp);
		else
			vput(nd.ni_dvp);
		if (nd.ni_vp)
			vrele(nd.ni_vp);
		return (EEXIST);
	}
	if (vn_start_write(nd.ni_dvp, &mp, V_NOWAIT) != 0) {
		NDFREE(&nd, NDF_ONLY_PNBUF);
		vput(nd.ni_dvp);
		if ((error = vn_start_write(NULL, &mp, V_XSLEEP | PCATCH)) != 0)
			return (error);
		goto restart;
	}
	error = VOP_WHITEOUT(nd.ni_dvp, &nd.ni_cnd, DELETE);
	NDFREE(&nd, NDF_ONLY_PNBUF);
	vput(nd.ni_dvp);
	vn_finished_write(mp);
	return (error);
}