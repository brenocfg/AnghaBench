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
struct nfsdevice {struct nfsdevice* nfsdev_host; struct nfsdevice* nfsdev_flexaddr; struct nfsdevice* nfsdev_fileaddr; int /*<<< orphan*/ ** nfsdev_dsdir; int /*<<< orphan*/ * nfsdev_dvp; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_NFSDSTATE ; 
 int /*<<< orphan*/  atomic_add_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free (struct nfsdevice*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsrv_devidcnt ; 
 int nfsrv_dsdirsize ; 
 int /*<<< orphan*/  vrele (int /*<<< orphan*/ *) ; 

void
nfsrv_freeonedevid(struct nfsdevice *ds)
{
	int i;

	atomic_add_int(&nfsrv_devidcnt, -1);
	vrele(ds->nfsdev_dvp);
	for (i = 0; i < nfsrv_dsdirsize; i++)
		if (ds->nfsdev_dsdir[i] != NULL)
			vrele(ds->nfsdev_dsdir[i]);
	free(ds->nfsdev_fileaddr, M_NFSDSTATE);
	free(ds->nfsdev_flexaddr, M_NFSDSTATE);
	free(ds->nfsdev_host, M_NFSDSTATE);
	free(ds, M_NFSDSTATE);
}