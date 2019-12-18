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
struct nfslockhashhead {int dummy; } ;
struct nfsclienthashhead {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  list; int /*<<< orphan*/  mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_NFSDCLIENT ; 
 int /*<<< orphan*/  M_NFSDLOCKFILE ; 
 int /*<<< orphan*/  M_NFSDSESSION ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  NFSBZERO (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFSX_V2FH ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_v2pubfh ; 
 int /*<<< orphan*/ * nfsclienthash ; 
 int /*<<< orphan*/ * nfslockhash ; 
 int nfsrv_clienthashsize ; 
 int /*<<< orphan*/  nfsrv_dontlisthead ; 
 int nfsrv_lockhashsize ; 
 int /*<<< orphan*/  nfsrv_recalllisthead ; 
 int nfsrv_sessionhashsize ; 
 TYPE_1__* nfssessionhash ; 

void
nfsd_init(void)
{
	int i;
	static int inited = 0;

	if (inited)
		return;
	inited = 1;

	/*
	 * Initialize client queues. Don't free/reinitialize
	 * them when nfsds are restarted.
	 */
	nfsclienthash = malloc(sizeof(struct nfsclienthashhead) *
	    nfsrv_clienthashsize, M_NFSDCLIENT, M_WAITOK | M_ZERO);
	for (i = 0; i < nfsrv_clienthashsize; i++)
		LIST_INIT(&nfsclienthash[i]);
	nfslockhash = malloc(sizeof(struct nfslockhashhead) *
	    nfsrv_lockhashsize, M_NFSDLOCKFILE, M_WAITOK | M_ZERO);
	for (i = 0; i < nfsrv_lockhashsize; i++)
		LIST_INIT(&nfslockhash[i]);
	nfssessionhash = malloc(sizeof(struct nfssessionhash) *
	    nfsrv_sessionhashsize, M_NFSDSESSION, M_WAITOK | M_ZERO);
	for (i = 0; i < nfsrv_sessionhashsize; i++) {
		mtx_init(&nfssessionhash[i].mtx, "nfssm", NULL, MTX_DEF);
		LIST_INIT(&nfssessionhash[i].list);
	}
	LIST_INIT(&nfsrv_dontlisthead);
	TAILQ_INIT(&nfsrv_recalllisthead);

	/* and the v2 pubfh should be all zeros */
	NFSBZERO(nfs_v2pubfh, NFSX_V2FH);
}