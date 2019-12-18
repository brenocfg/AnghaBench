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
struct nfssessionhash {int dummy; } ;
struct nfsrv_descript {int /*<<< orphan*/  nd_sessionid; } ;
struct nfsdsession {TYPE_1__* sess_clp; } ;
struct TYPE_2__ {int lc_flags; } ;

/* Variables and functions */
 int LCL_RECLAIMCOMPLETE ; 
 int LCL_RECLAIMONEFS ; 
 int NFSERR_BADSESSION ; 
 int NFSERR_COMPLETEALREADY ; 
 int /*<<< orphan*/  NFSLOCKSESSION (struct nfssessionhash*) ; 
 int /*<<< orphan*/  NFSLOCKSTATE () ; 
 struct nfssessionhash* NFSSESSIONHASH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFSUNLOCKSESSION (struct nfssessionhash*) ; 
 int /*<<< orphan*/  NFSUNLOCKSTATE () ; 
 struct nfsdsession* nfsrv_findsession (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsrv_markreclaim (TYPE_1__*) ; 

int
nfsrv_checkreclaimcomplete(struct nfsrv_descript *nd, int onefs)
{
	struct nfsdsession *sep;
	struct nfssessionhash *shp;
	int error = 0;

	shp = NFSSESSIONHASH(nd->nd_sessionid);
	NFSLOCKSTATE();
	NFSLOCKSESSION(shp);
	sep = nfsrv_findsession(nd->nd_sessionid);
	if (sep == NULL) {
		NFSUNLOCKSESSION(shp);
		NFSUNLOCKSTATE();
		return (NFSERR_BADSESSION);
	}

	if (onefs != 0)
		sep->sess_clp->lc_flags |= LCL_RECLAIMONEFS;
		/* Check to see if reclaim complete has already happened. */
	else if ((sep->sess_clp->lc_flags & LCL_RECLAIMCOMPLETE) != 0)
		error = NFSERR_COMPLETEALREADY;
	else {
		sep->sess_clp->lc_flags |= LCL_RECLAIMCOMPLETE;
		nfsrv_markreclaim(sep->sess_clp);
	}
	NFSUNLOCKSESSION(shp);
	NFSUNLOCKSTATE();
	return (error);
}