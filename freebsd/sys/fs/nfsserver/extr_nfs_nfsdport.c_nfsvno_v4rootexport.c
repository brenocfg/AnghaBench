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
struct ucred {int dummy; } ;
struct nfsrv_descript {int /*<<< orphan*/  nd_flag; int /*<<< orphan*/  nd_nam; } ;

/* Variables and functions */
 int AUTH_SYS ; 
 int /*<<< orphan*/  ND_EXAUTHSYS ; 
 int /*<<< orphan*/  ND_EXGSS ; 
 int /*<<< orphan*/  ND_EXGSSINTEGRITY ; 
 int /*<<< orphan*/  ND_EXGSSPRIVACY ; 
 int NFSERR_PROGUNAVAIL ; 
 int /*<<< orphan*/  NFSEXITCODE (int) ; 
 int RPCSEC_GSS_KRB5 ; 
 int RPCSEC_GSS_KRB5I ; 
 int RPCSEC_GSS_KRB5P ; 
 int /*<<< orphan*/  crfree (struct ucred*) ; 
 int /*<<< orphan*/  nfsv4root_mnt ; 
 int vfs_stdcheckexp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,struct ucred**,int*,int**) ; 

int
nfsvno_v4rootexport(struct nfsrv_descript *nd)
{
	struct ucred *credanon;
	int exflags, error = 0, numsecflavor, *secflavors, i;

	error = vfs_stdcheckexp(&nfsv4root_mnt, nd->nd_nam, &exflags,
	    &credanon, &numsecflavor, &secflavors);
	if (error) {
		error = NFSERR_PROGUNAVAIL;
		goto out;
	}
	if (credanon != NULL)
		crfree(credanon);
	for (i = 0; i < numsecflavor; i++) {
		if (secflavors[i] == AUTH_SYS)
			nd->nd_flag |= ND_EXAUTHSYS;
		else if (secflavors[i] == RPCSEC_GSS_KRB5)
			nd->nd_flag |= ND_EXGSS;
		else if (secflavors[i] == RPCSEC_GSS_KRB5I)
			nd->nd_flag |= ND_EXGSSINTEGRITY;
		else if (secflavors[i] == RPCSEC_GSS_KRB5P)
			nd->nd_flag |= ND_EXGSSPRIVACY;
	}

out:
	NFSEXITCODE(error);
	return (error);
}