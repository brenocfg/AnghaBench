#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  spc_root; scalar_t__ spc_indblkshift; scalar_t__ spc_datablkszsec; int /*<<< orphan*/ * spc_scn; int /*<<< orphan*/  spc_refcnt; } ;
typedef  TYPE_1__ scan_prefetch_ctx_t ;
typedef  int /*<<< orphan*/  dsl_scan_t ;
struct TYPE_7__ {scalar_t__ dn_indblkshift; scalar_t__ dn_datablkszsec; } ;
typedef  TYPE_2__ dnode_phys_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 TYPE_1__* kmem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_refcount_add (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  zfs_refcount_create (int /*<<< orphan*/ *) ; 

__attribute__((used)) static scan_prefetch_ctx_t *
scan_prefetch_ctx_create(dsl_scan_t *scn, dnode_phys_t *dnp, void *tag)
{
	scan_prefetch_ctx_t *spc;

	spc = kmem_alloc(sizeof (scan_prefetch_ctx_t), KM_SLEEP);
	zfs_refcount_create(&spc->spc_refcnt);
	zfs_refcount_add(&spc->spc_refcnt, tag);
	spc->spc_scn = scn;
	if (dnp != NULL) {
		spc->spc_datablkszsec = dnp->dn_datablkszsec;
		spc->spc_indblkshift = dnp->dn_indblkshift;
		spc->spc_root = B_FALSE;
	} else {
		spc->spc_datablkszsec = 0;
		spc->spc_indblkshift = 0;
		spc->spc_root = B_TRUE;
	}

	return (spc);
}