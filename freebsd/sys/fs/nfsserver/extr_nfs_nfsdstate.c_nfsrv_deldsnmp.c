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
struct nfsmount {int dummy; } ;
struct nfsdevice {char* nfsdev_host; int /*<<< orphan*/  nfsdev_deviceid; } ;
typedef  int /*<<< orphan*/  NFSPROC_T ;

/* Variables and functions */
 int /*<<< orphan*/  NFSDDSLOCK () ; 
 int /*<<< orphan*/  NFSDDSUNLOCK () ; 
 int /*<<< orphan*/  NFSD_DEBUG (int,char*) ; 
 int PNFSDOP_FORCEDELDS ; 
 int /*<<< orphan*/  nfsrv_deleteds (struct nfsdevice*) ; 
 struct nfsdevice* nfsrv_findmirroredds (struct nfsmount*) ; 
 int /*<<< orphan*/  nfsrv_flexmirrordel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct nfsdevice* nfsv4_findmirror (struct nfsmount*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

struct nfsdevice *
nfsrv_deldsnmp(int op, struct nfsmount *nmp, NFSPROC_T *p)
{
	struct nfsdevice *fndds;

	NFSD_DEBUG(4, "deldsdvp\n");
	NFSDDSLOCK();
	if (op == PNFSDOP_FORCEDELDS)
		fndds = nfsv4_findmirror(nmp);
	else
		fndds = nfsrv_findmirroredds(nmp);
	if (fndds != NULL)
		nfsrv_deleteds(fndds);
	NFSDDSUNLOCK();
	if (fndds != NULL) {
		if (op != PNFSDOP_FORCEDELDS)
			nfsrv_flexmirrordel(fndds->nfsdev_deviceid, p);
		printf("pNFS server: mirror %s failed\n", fndds->nfsdev_host);
	}
	return (fndds);
}