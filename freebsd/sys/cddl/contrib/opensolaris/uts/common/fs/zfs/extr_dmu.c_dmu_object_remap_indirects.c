#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long long uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
struct TYPE_8__ {int dn_nlevels; unsigned long long dn_indblkshift; unsigned long long dn_datablkshift; int /*<<< orphan*/  dn_object; } ;
typedef  TYPE_1__ dnode_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINTR ; 
 int /*<<< orphan*/  FORREAL ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  JUSTLOOKING ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 unsigned long long SPA_BLKPTRSHIFT ; 
 int /*<<< orphan*/  TXG_WAIT ; 
 int dmu_object_remap_one_indirect (int /*<<< orphan*/ *,TYPE_1__*,unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  dmu_tx_abort (int /*<<< orphan*/ *) ; 
 int dmu_tx_assign (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_tx_commit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dmu_tx_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_tx_hold_bonus (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dnode_hold (int /*<<< orphan*/ *,unsigned long long,int /*<<< orphan*/ ,TYPE_1__**) ; 
 scalar_t__ dnode_needs_remap (TYPE_1__*) ; 
 scalar_t__ dnode_next_offset (TYPE_1__*,int /*<<< orphan*/ ,unsigned long long*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dnode_rele (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dnode_setdirty (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ issig (int /*<<< orphan*/ ) ; 

int
dmu_object_remap_indirects(objset_t *os, uint64_t object,
    uint64_t last_removal_txg)
{
	uint64_t offset, l1span;
	int err;
	dnode_t *dn;

	err = dnode_hold(os, object, FTAG, &dn);
	if (err != 0) {
		return (err);
	}

	if (dn->dn_nlevels <= 1) {
		if (issig(JUSTLOOKING) && issig(FORREAL)) {
			err = SET_ERROR(EINTR);
		}

		/*
		 * If the dnode has no indirect blocks, we cannot dirty them.
		 * We still want to remap the blkptr(s) in the dnode if
		 * appropriate, so mark it as dirty.
		 */
		if (err == 0 && dnode_needs_remap(dn)) {
			dmu_tx_t *tx = dmu_tx_create(os);
			dmu_tx_hold_bonus(tx, dn->dn_object);
			if ((err = dmu_tx_assign(tx, TXG_WAIT)) == 0) {
				dnode_setdirty(dn, tx);
				dmu_tx_commit(tx);
			} else {
				dmu_tx_abort(tx);
			}
		}

		dnode_rele(dn, FTAG);
		return (err);
	}

	offset = 0;
	l1span = 1ULL << (dn->dn_indblkshift - SPA_BLKPTRSHIFT +
	    dn->dn_datablkshift);
	/*
	 * Find the next L1 indirect that is not a hole.
	 */
	while (dnode_next_offset(dn, 0, &offset, 2, 1, 0) == 0) {
		if (issig(JUSTLOOKING) && issig(FORREAL)) {
			err = SET_ERROR(EINTR);
			break;
		}
		if ((err = dmu_object_remap_one_indirect(os, dn,
		    last_removal_txg, offset)) != 0) {
			break;
		}
		offset += l1span;
	}

	dnode_rele(dn, FTAG);
	return (err);
}