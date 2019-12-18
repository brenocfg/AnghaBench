#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zbookmark_phys_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  dsl_scan_t ;
struct TYPE_8__ {int /*<<< orphan*/  ds_object; } ;
typedef  TYPE_1__ dsl_dataset_t ;
struct TYPE_9__ {int dn_nblkptr; int dn_flags; int /*<<< orphan*/ * dn_blkptr; scalar_t__ dn_nlevels; } ;
typedef  TYPE_2__ dnode_phys_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
typedef  int /*<<< orphan*/  dmu_objset_type_t ;

/* Variables and functions */
 int DMU_SPILL_BLKID ; 
 int DNODE_FLAG_SPILL_BLKPTR ; 
 int /*<<< orphan*/ * DN_SPILL_BLKPTR (TYPE_2__*) ; 
 int /*<<< orphan*/  SET_BOOKMARK (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  dsl_scan_visitbp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dsl_scan_visitdnode(dsl_scan_t *scn, dsl_dataset_t *ds,
    dmu_objset_type_t ostype, dnode_phys_t *dnp,
    uint64_t object, dmu_tx_t *tx)
{
	int j;

	for (j = 0; j < dnp->dn_nblkptr; j++) {
		zbookmark_phys_t czb;

		SET_BOOKMARK(&czb, ds ? ds->ds_object : 0, object,
		    dnp->dn_nlevels - 1, j);
		dsl_scan_visitbp(&dnp->dn_blkptr[j],
		    &czb, dnp, ds, scn, ostype, tx);
	}

	if (dnp->dn_flags & DNODE_FLAG_SPILL_BLKPTR) {
		zbookmark_phys_t czb;
		SET_BOOKMARK(&czb, ds ? ds->ds_object : 0, object,
		    0, DMU_SPILL_BLKID);
		dsl_scan_visitbp(DN_SPILL_BLKPTR(dnp),
		    &czb, dnp, ds, scn, ostype, tx);
	}
}