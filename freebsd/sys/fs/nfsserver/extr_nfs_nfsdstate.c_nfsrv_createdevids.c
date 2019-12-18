#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nfslayouthash {int dummy; } ;
struct nfsdevice {int dummy; } ;
struct nfsd_nfsd_args {char* addr; char* dnshost; char* dspath; char* mdspath; int mirrorcnt; int addrlen; int dnshostlen; int dspathlen; int mdspathlen; } ;
struct TYPE_3__ {int /*<<< orphan*/  list; int /*<<< orphan*/  mtx; } ;
typedef  int /*<<< orphan*/  NFSPROC_T ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_NFSDSESSION ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 TYPE_1__* mallocarray (int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* nfslayouthash ; 
 int /*<<< orphan*/  nfsrv_allocdevid (struct nfsdevice*,char*,char*) ; 
 int nfsrv_devidcnt ; 
 int nfsrv_faildscnt ; 
 int /*<<< orphan*/  nfsrv_freealldevids () ; 
 int nfsrv_layouthashsize ; 
 int nfsrv_layouthighwater ; 
 int nfsrv_maxpnfsmirror ; 
 int nfsrv_setdsserver (char*,char*,int /*<<< orphan*/ *,struct nfsdevice**) ; 
 scalar_t__ strlen (char*) ; 

int
nfsrv_createdevids(struct nfsd_nfsd_args *args, NFSPROC_T *p)
{
	struct nfsdevice *ds;
	char *addrp, *dnshostp, *dspathp, *mdspathp;
	int error, i;

	addrp = args->addr;
	dnshostp = args->dnshost;
	dspathp = args->dspath;
	mdspathp = args->mdspath;
	nfsrv_maxpnfsmirror = args->mirrorcnt;
	if (addrp == NULL || dnshostp == NULL || dspathp == NULL ||
	    mdspathp == NULL)
		return (0);

	/*
	 * Loop around for each nul-terminated string in args->addr,
	 * args->dnshost, args->dnspath and args->mdspath.
	 */
	while (addrp < (args->addr + args->addrlen) &&
	    dnshostp < (args->dnshost + args->dnshostlen) &&
	    dspathp < (args->dspath + args->dspathlen) &&
	    mdspathp < (args->mdspath + args->mdspathlen)) {
		error = nfsrv_setdsserver(dspathp, mdspathp, p, &ds);
		if (error != 0) {
			/* Free all DS servers. */
			nfsrv_freealldevids();
			nfsrv_devidcnt = 0;
			return (ENXIO);
		}
		nfsrv_allocdevid(ds, addrp, dnshostp);
		addrp += (strlen(addrp) + 1);
		dnshostp += (strlen(dnshostp) + 1);
		dspathp += (strlen(dspathp) + 1);
		mdspathp += (strlen(mdspathp) + 1);
	}
	if (nfsrv_devidcnt < nfsrv_maxpnfsmirror) {
		/* Free all DS servers. */
		nfsrv_freealldevids();
		nfsrv_devidcnt = 0;
		nfsrv_maxpnfsmirror = 1;
		return (ENXIO);
	}
	/* We can fail at most one less DS than the mirror level. */
	nfsrv_faildscnt = nfsrv_maxpnfsmirror - 1;

	/*
	 * Allocate the nfslayout hash table now, since this is a pNFS server.
	 * Make it 1% of the high water mark and at least 100.
	 */
	if (nfslayouthash == NULL) {
		nfsrv_layouthashsize = nfsrv_layouthighwater / 100;
		if (nfsrv_layouthashsize < 100)
			nfsrv_layouthashsize = 100;
		nfslayouthash = mallocarray(nfsrv_layouthashsize,
		    sizeof(struct nfslayouthash), M_NFSDSESSION, M_WAITOK |
		    M_ZERO);
		for (i = 0; i < nfsrv_layouthashsize; i++) {
			mtx_init(&nfslayouthash[i].mtx, "nfslm", NULL, MTX_DEF);
			TAILQ_INIT(&nfslayouthash[i].list);
		}
	}
	return (0);
}