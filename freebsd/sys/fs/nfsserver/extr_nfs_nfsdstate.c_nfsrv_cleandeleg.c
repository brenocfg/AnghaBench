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
typedef  int /*<<< orphan*/  vnode_t ;
struct nfsstate {struct nfsclient* ls_clp; } ;
struct nfslockfile {int /*<<< orphan*/  lf_deleg; } ;
struct nfsclient {int dummy; } ;
typedef  int /*<<< orphan*/  NFSPROC_T ;

/* Variables and functions */
 struct nfsstate* LIST_END (int /*<<< orphan*/ *) ; 
 struct nfsstate* LIST_FIRST (int /*<<< orphan*/ *) ; 
 struct nfsstate* LIST_NEXT (struct nfsstate*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFSEXITCODE (int) ; 
 int /*<<< orphan*/  ls_file ; 
 int nfsrv_delegconflict (struct nfsstate*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfsrv_cleandeleg(vnode_t vp, struct nfslockfile *lfp,
    struct nfsclient *clp, int *haslockp, NFSPROC_T *p)
{
	struct nfsstate *stp, *nstp;
	int ret = 0;

	stp = LIST_FIRST(&lfp->lf_deleg);
	while (stp != LIST_END(&lfp->lf_deleg)) {
		nstp = LIST_NEXT(stp, ls_file);
		if (stp->ls_clp != clp) {
			ret = nfsrv_delegconflict(stp, haslockp, p, vp);
			if (ret) {
				/*
				 * nfsrv_delegconflict() unlocks state
				 * when it returns non-zero.
				 */
				goto out;
			}
		}
		stp = nstp;
	}
out:
	NFSEXITCODE(ret);
	return (ret);
}