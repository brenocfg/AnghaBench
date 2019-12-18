#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;
struct TYPE_17__ {TYPE_1__* os_phys; int /*<<< orphan*/  os_flags; } ;
typedef  TYPE_2__ objset_t ;
typedef  int /*<<< orphan*/  dsl_dataset_t ;
struct TYPE_18__ {scalar_t__ dn_datablkshift; int dn_indblkshift; int* dn_next_nlevels; int dn_nlevels; scalar_t__ dn_nblkptr; } ;
typedef  TYPE_3__ dnode_t ;
struct TYPE_19__ {size_t tx_txg; } ;
typedef  TYPE_4__ dmu_tx_t ;
typedef  scalar_t__ dmu_objset_type_t ;
typedef  int /*<<< orphan*/  blkptr_t ;
struct TYPE_16__ {int /*<<< orphan*/  os_flags; scalar_t__ os_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 TYPE_3__* DMU_META_DNODE (TYPE_2__*) ; 
 scalar_t__ DMU_OST_ANY ; 
 scalar_t__ DMU_OST_NONE ; 
 scalar_t__ DMU_OST_NUMTYPES ; 
 int /*<<< orphan*/  DMU_OT_DNODE ; 
 int /*<<< orphan*/  DMU_OT_NONE ; 
 int /*<<< orphan*/  DNODE_BLOCK_SIZE ; 
 int /*<<< orphan*/  DNODE_MIN_SLOTS ; 
 scalar_t__ DNODE_SHIFT ; 
 int /*<<< orphan*/  DN_MAX_INDBLKSHIFT ; 
 scalar_t__ DN_MAX_OBJECT ; 
 int /*<<< orphan*/  OBJSET_FLAG_USERACCOUNTING_COMPLETE ; 
 int SPA_BLKPTRSHIFT ; 
 size_t TXG_MASK ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_objset_from_ds (int /*<<< orphan*/ *,TYPE_2__**) ; 
 int /*<<< orphan*/  dmu_objset_open_impl (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__**) ; 
 scalar_t__ dmu_objset_userused_enabled (TYPE_2__*) ; 
 int dmu_tx_is_syncing (TYPE_4__*) ; 
 int /*<<< orphan*/  dnode_allocate (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  dsl_dataset_dirty (int /*<<< orphan*/ *,TYPE_4__*) ; 

objset_t *
dmu_objset_create_impl(spa_t *spa, dsl_dataset_t *ds, blkptr_t *bp,
    dmu_objset_type_t type, dmu_tx_t *tx)
{
	objset_t *os;
	dnode_t *mdn;

	ASSERT(dmu_tx_is_syncing(tx));

	if (ds != NULL)
		VERIFY0(dmu_objset_from_ds(ds, &os));
	else
		VERIFY0(dmu_objset_open_impl(spa, NULL, bp, &os));

	mdn = DMU_META_DNODE(os);

	dnode_allocate(mdn, DMU_OT_DNODE, DNODE_BLOCK_SIZE, DN_MAX_INDBLKSHIFT,
	    DMU_OT_NONE, 0, DNODE_MIN_SLOTS, tx);

	/*
	 * We don't want to have to increase the meta-dnode's nlevels
	 * later, because then we could do it in quescing context while
	 * we are also accessing it in open context.
	 *
	 * This precaution is not necessary for the MOS (ds == NULL),
	 * because the MOS is only updated in syncing context.
	 * This is most fortunate: the MOS is the only objset that
	 * needs to be synced multiple times as spa_sync() iterates
	 * to convergence, so minimizing its dn_nlevels matters.
	 */
	if (ds != NULL) {
		int levels = 1;

		/*
		 * Determine the number of levels necessary for the meta-dnode
		 * to contain DN_MAX_OBJECT dnodes.  Note that in order to
		 * ensure that we do not overflow 64 bits, there has to be
		 * a nlevels that gives us a number of blocks > DN_MAX_OBJECT
		 * but < 2^64.  Therefore,
		 * (mdn->dn_indblkshift - SPA_BLKPTRSHIFT) (10) must be
		 * less than (64 - log2(DN_MAX_OBJECT)) (16).
		 */
		while ((uint64_t)mdn->dn_nblkptr <<
		    (mdn->dn_datablkshift - DNODE_SHIFT +
		    (levels - 1) * (mdn->dn_indblkshift - SPA_BLKPTRSHIFT)) <
		    DN_MAX_OBJECT)
			levels++;

		mdn->dn_next_nlevels[tx->tx_txg & TXG_MASK] =
		    mdn->dn_nlevels = levels;
	}

	ASSERT(type != DMU_OST_NONE);
	ASSERT(type != DMU_OST_ANY);
	ASSERT(type < DMU_OST_NUMTYPES);
	os->os_phys->os_type = type;
	if (dmu_objset_userused_enabled(os)) {
		os->os_phys->os_flags |= OBJSET_FLAG_USERACCOUNTING_COMPLETE;
		os->os_flags = os->os_phys->os_flags;
	}

	dsl_dataset_dirty(ds, tx);

	return (os);
}