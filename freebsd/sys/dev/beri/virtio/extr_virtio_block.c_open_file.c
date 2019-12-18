#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct vattr {int dummy; } ;
struct thread {int /*<<< orphan*/  td_ucred; } ;
struct nameidata {TYPE_2__* ni_vp; } ;
struct beri_vtblk_softc {int /*<<< orphan*/  cred; TYPE_2__* vnode; TYPE_1__* mdio; } ;
struct TYPE_7__ {scalar_t__ v_type; int v_iflag; int /*<<< orphan*/  v_vflag; } ;
struct TYPE_6__ {int /*<<< orphan*/  md_file; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FOLLOW ; 
 int FREAD ; 
 int FWRITE ; 
 scalar_t__ LK_EXCLUSIVE ; 
 int LK_RETRY ; 
 int LK_UPGRADE ; 
 int /*<<< orphan*/  LOOKUP ; 
 int /*<<< orphan*/  NDFREE (struct nameidata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NDF_ONLY_PNBUF ; 
 int /*<<< orphan*/  NDINIT (struct nameidata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct thread*) ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int VI_DOOMED ; 
 int VOP_GETATTR (TYPE_2__*,struct vattr*,int /*<<< orphan*/ ) ; 
 scalar_t__ VOP_ISLOCKED (TYPE_2__*) ; 
 int /*<<< orphan*/  VOP_UNLOCK (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ VREG ; 
 int /*<<< orphan*/  VV_MD ; 
 int /*<<< orphan*/  crhold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vn_lock (TYPE_2__*,int) ; 
 int vn_open (struct nameidata*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
open_file(struct beri_vtblk_softc *sc, struct thread *td)
{
	struct nameidata nd;
	struct vattr vattr;
	int error;
	int flags;

	flags = (FREAD | FWRITE);
	NDINIT(&nd, LOOKUP, FOLLOW, UIO_SYSSPACE,
		sc->mdio->md_file, td);
	error = vn_open(&nd, &flags, 0, NULL);
	if (error != 0)
		return (error);
	NDFREE(&nd, NDF_ONLY_PNBUF);

	if (nd.ni_vp->v_type != VREG) {
		return (EINVAL);
	}

	error = VOP_GETATTR(nd.ni_vp, &vattr, td->td_ucred);
	if (error != 0)
		return (error);

	if (VOP_ISLOCKED(nd.ni_vp) != LK_EXCLUSIVE) {
		vn_lock(nd.ni_vp, LK_UPGRADE | LK_RETRY);
		if (nd.ni_vp->v_iflag & VI_DOOMED) {
			return (1);
		}
	}
	nd.ni_vp->v_vflag |= VV_MD;
	VOP_UNLOCK(nd.ni_vp, 0);

	sc->vnode = nd.ni_vp;
	sc->cred = crhold(td->td_ucred);

	return (0);
}