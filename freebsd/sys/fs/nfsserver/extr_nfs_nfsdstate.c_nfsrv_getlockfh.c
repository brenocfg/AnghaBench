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
typedef  int u_short ;
struct nfslockfile {int /*<<< orphan*/  lf_fh; } ;
typedef  int /*<<< orphan*/  fhandle_t ;
typedef  int /*<<< orphan*/  NFSPROC_T ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  NFSEXITCODE (int) ; 
 int NFSLCK_OPEN ; 
 int nfsvno_getfh (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static int
nfsrv_getlockfh(vnode_t vp, u_short flags, struct nfslockfile *new_lfp,
    fhandle_t *nfhp, NFSPROC_T *p)
{
	fhandle_t *fhp = NULL;
	int error;

	/*
	 * For lock, use the new nfslock structure, otherwise just
	 * a fhandle_t on the stack.
	 */
	if (flags & NFSLCK_OPEN) {
		KASSERT(new_lfp != NULL, ("nfsrv_getlockfh: new_lfp NULL"));
		fhp = &new_lfp->lf_fh;
	} else if (nfhp) {
		fhp = nfhp;
	} else {
		panic("nfsrv_getlockfh");
	}
	error = nfsvno_getfh(vp, fhp, p);
	NFSEXITCODE(error);
	return (error);
}