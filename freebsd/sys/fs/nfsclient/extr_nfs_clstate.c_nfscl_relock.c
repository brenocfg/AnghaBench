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
typedef  int /*<<< orphan*/  vnode_t ;
typedef  scalar_t__ u_int64_t ;
struct ucred {int dummy; } ;
struct nfsmount {int dummy; } ;
struct nfsfh {int /*<<< orphan*/  nfh_len; int /*<<< orphan*/  nfh_fh; } ;
struct nfscllockowner {int /*<<< orphan*/  nfsl_openowner; int /*<<< orphan*/  nfsl_owner; int /*<<< orphan*/  nfsl_lockflags; } ;
struct nfscllock {int /*<<< orphan*/  nfslo_type; scalar_t__ nfslo_first; scalar_t__ nfslo_end; } ;
struct nfsclclient {int dummy; } ;
struct TYPE_2__ {struct nfsfh* n_fhp; } ;
typedef  int /*<<< orphan*/  NFSPROC_T ;

/* Variables and functions */
 TYPE_1__* VTONFS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfscl_freelockowner (struct nfscllockowner*,int /*<<< orphan*/ ) ; 
 int nfscl_getbytelock (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,struct ucred*,int /*<<< orphan*/ *,struct nfsclclient*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nfscllockowner**,int*,int*) ; 
 int nfscl_trylock (struct nfsmount*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nfscllockowner*,int,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,struct ucred*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nfscl_relock(vnode_t vp, struct nfsclclient *clp, struct nfsmount *nmp,
    struct nfscllockowner *lp, struct nfscllock *lop, struct ucred *cred,
    NFSPROC_T *p)
{
	struct nfscllockowner *nlp;
	struct nfsfh *nfhp;
	u_int64_t off, len;
	int error, newone, donelocally;

	off = lop->nfslo_first;
	len = lop->nfslo_end - lop->nfslo_first;
	error = nfscl_getbytelock(vp, off, len, lop->nfslo_type, cred, p,
	    clp, 1, NULL, lp->nfsl_lockflags, lp->nfsl_owner,
	    lp->nfsl_openowner, &nlp, &newone, &donelocally);
	if (error || donelocally)
		return (error);
	nfhp = VTONFS(vp)->n_fhp;
	error = nfscl_trylock(nmp, vp, nfhp->nfh_fh,
	    nfhp->nfh_len, nlp, newone, 0, off,
	    len, lop->nfslo_type, cred, p);
	if (error)
		nfscl_freelockowner(nlp, 0);
	return (error);
}