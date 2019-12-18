#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ucred {scalar_t__ cr_uid; int /*<<< orphan*/  cr_groups; int /*<<< orphan*/  cr_ngroups; int /*<<< orphan*/  cr_gid; } ;
struct nfsrv_descript {int nd_flag; scalar_t__ nd_procnum; TYPE_1__* nd_cred; } ;
struct nfsexstuff {int /*<<< orphan*/  nes_exflag; } ;
struct TYPE_4__ {scalar_t__ cr_uid; int /*<<< orphan*/  cr_gid; } ;

/* Variables and functions */
 int AUTH_TOOWEAK ; 
 int /*<<< orphan*/  MNT_EXPORTANON ; 
 int ND_AUTHNONE ; 
 int ND_GSS ; 
 int ND_NFSV4 ; 
 int NFSERR_AUTHERR ; 
 int NFSERR_PROGNOTV4 ; 
 int NFSERR_WRONGSEC ; 
 int /*<<< orphan*/  NFSEXITCODE2 (int,struct nfsrv_descript*) ; 
 scalar_t__ NFSPROC_FSINFO ; 
 scalar_t__ NFSV4OP_SECINFO ; 
 scalar_t__ NFSVNO_EXPORTANON (struct nfsexstuff*) ; 
 scalar_t__ NFSVNO_EXPORTED (struct nfsexstuff*) ; 
 scalar_t__ NFSVNO_EXV4ONLY (struct nfsexstuff*) ; 
 int /*<<< orphan*/  crsetgroups (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* nfsrv_getgrpscred (TYPE_1__*) ; 
 scalar_t__ nfsvno_testexp (struct nfsrv_descript*,struct nfsexstuff*) ; 

int
nfsd_excred(struct nfsrv_descript *nd, struct nfsexstuff *exp,
    struct ucred *credanon)
{
	int error = 0;

	/*
	 * Check/setup credentials.
	 */
	if (nd->nd_flag & ND_GSS)
		exp->nes_exflag &= ~MNT_EXPORTANON;

	/*
	 * Check to see if the operation is allowed for this security flavor.
	 * RFC2623 suggests that the NFSv3 Fsinfo RPC be allowed to
	 * AUTH_NONE or AUTH_SYS for file systems requiring RPCSEC_GSS.
	 * Also, allow Secinfo, so that it can acquire the correct flavor(s).
	 */
	if (nfsvno_testexp(nd, exp) &&
	    nd->nd_procnum != NFSV4OP_SECINFO &&
	    nd->nd_procnum != NFSPROC_FSINFO) {
		if (nd->nd_flag & ND_NFSV4)
			error = NFSERR_WRONGSEC;
		else
			error = (NFSERR_AUTHERR | AUTH_TOOWEAK);
		goto out;
	}

	/*
	 * Check to see if the file system is exported V4 only.
	 */
	if (NFSVNO_EXV4ONLY(exp) && !(nd->nd_flag & ND_NFSV4)) {
		error = NFSERR_PROGNOTV4;
		goto out;
	}

	/*
	 * Now, map the user credentials.
	 * (Note that ND_AUTHNONE will only be set for an NFSv3
	 *  Fsinfo RPC. If set for anything else, this code might need
	 *  to change.)
	 */
	if (NFSVNO_EXPORTED(exp)) {
		if (((nd->nd_flag & ND_GSS) == 0 && nd->nd_cred->cr_uid == 0) ||
		     NFSVNO_EXPORTANON(exp) ||
		     (nd->nd_flag & ND_AUTHNONE) != 0) {
			nd->nd_cred->cr_uid = credanon->cr_uid;
			nd->nd_cred->cr_gid = credanon->cr_gid;
			crsetgroups(nd->nd_cred, credanon->cr_ngroups,
			    credanon->cr_groups);
		} else if ((nd->nd_flag & ND_GSS) == 0) {
			/*
			 * If using AUTH_SYS, call nfsrv_getgrpscred() to see
			 * if there is a replacement credential with a group
			 * list set up by "nfsuserd -manage-gids".
			 * If there is no replacement, nfsrv_getgrpscred()
			 * simply returns its argument.
			 */
			nd->nd_cred = nfsrv_getgrpscred(nd->nd_cred);
		}
	}

out:
	NFSEXITCODE2(error, nd);
	return (error);
}