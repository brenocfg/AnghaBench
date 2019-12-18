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
typedef  int u_int ;
struct TYPE_2__ {int cn_flags; int /*<<< orphan*/  cn_pnbuf; } ;
struct nameidata {int /*<<< orphan*/ * ni_startdir; TYPE_1__ ni_cnd; int /*<<< orphan*/ * ni_dvp; int /*<<< orphan*/ * ni_vp; } ;

/* Variables and functions */
 int HASBUF ; 
 int LOCKLEAF ; 
 int LOCKPARENT ; 
 int const NDF_NO_DVP_RELE ; 
 int const NDF_NO_DVP_UNLOCK ; 
 int const NDF_NO_FREE_PNBUF ; 
 int const NDF_NO_STARTDIR_RELE ; 
 int const NDF_NO_VP_RELE ; 
 int const NDF_NO_VP_UNLOCK ; 
 int SAVESTART ; 
 int /*<<< orphan*/  VOP_UNLOCK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int WANTPARENT ; 
 int /*<<< orphan*/  namei_zone ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vput (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vrele (int /*<<< orphan*/ *) ; 

void
NDFREE(struct nameidata *ndp, const u_int flags)
{
	int unlock_dvp;
	int unlock_vp;

	unlock_dvp = 0;
	unlock_vp = 0;

	if (!(flags & NDF_NO_FREE_PNBUF) &&
	    (ndp->ni_cnd.cn_flags & HASBUF)) {
		uma_zfree(namei_zone, ndp->ni_cnd.cn_pnbuf);
		ndp->ni_cnd.cn_flags &= ~HASBUF;
	}
	if (!(flags & NDF_NO_VP_UNLOCK) &&
	    (ndp->ni_cnd.cn_flags & LOCKLEAF) && ndp->ni_vp)
		unlock_vp = 1;
	if (!(flags & NDF_NO_DVP_UNLOCK) &&
	    (ndp->ni_cnd.cn_flags & LOCKPARENT) &&
	    ndp->ni_dvp != ndp->ni_vp)
		unlock_dvp = 1;
	if (!(flags & NDF_NO_VP_RELE) && ndp->ni_vp) {
		if (unlock_vp) {
			vput(ndp->ni_vp);
			unlock_vp = 0;
		} else
			vrele(ndp->ni_vp);
		ndp->ni_vp = NULL;
	}
	if (unlock_vp)
		VOP_UNLOCK(ndp->ni_vp, 0);
	if (!(flags & NDF_NO_DVP_RELE) &&
	    (ndp->ni_cnd.cn_flags & (LOCKPARENT|WANTPARENT))) {
		if (unlock_dvp) {
			vput(ndp->ni_dvp);
			unlock_dvp = 0;
		} else
			vrele(ndp->ni_dvp);
		ndp->ni_dvp = NULL;
	}
	if (unlock_dvp)
		VOP_UNLOCK(ndp->ni_dvp, 0);
	if (!(flags & NDF_NO_STARTDIR_RELE) &&
	    (ndp->ni_cnd.cn_flags & SAVESTART)) {
		vrele(ndp->ni_startdir);
		ndp->ni_startdir = NULL;
	}
}