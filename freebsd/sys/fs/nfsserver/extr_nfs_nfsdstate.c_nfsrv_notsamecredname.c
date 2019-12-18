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
struct nfsrv_descript {int nd_flag; scalar_t__ nd_princlen; TYPE_1__* nd_cred; int /*<<< orphan*/  nd_principal; } ;
struct nfsclient {int lc_flags; scalar_t__ lc_namelen; scalar_t__ lc_uid; int /*<<< orphan*/  lc_name; } ;
struct TYPE_2__ {scalar_t__ cr_uid; } ;

/* Variables and functions */
 int LCL_GSS ; 
 int LCL_NAME ; 
 int ND_GSS ; 
 scalar_t__ NFSBCMP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
nfsrv_notsamecredname(struct nfsrv_descript *nd, struct nfsclient *clp)
{

	if (nd->nd_flag & ND_GSS) {
		if (!(clp->lc_flags & LCL_GSS))
			return (1);
		if (clp->lc_flags & LCL_NAME) {
			if (nd->nd_princlen != clp->lc_namelen ||
			    NFSBCMP(nd->nd_principal, clp->lc_name,
				clp->lc_namelen))
				return (1);
			else
				return (0);
		}
		if (nd->nd_cred->cr_uid == clp->lc_uid)
			return (0);
		else
			return (1);
	} else if (clp->lc_flags & LCL_GSS)
		return (1);
	/*
	 * For AUTH_SYS, allow the same uid or root. (This is underspecified
	 * in RFC3530, which talks about principals, but doesn't say anything
	 * about uids for AUTH_SYS.)
	 */
	if (nd->nd_cred->cr_uid == clp->lc_uid || nd->nd_cred->cr_uid == 0)
		return (0);
	else
		return (1);
}