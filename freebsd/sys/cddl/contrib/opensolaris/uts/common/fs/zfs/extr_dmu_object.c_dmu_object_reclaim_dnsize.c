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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  dnode_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
typedef  int /*<<< orphan*/  dmu_object_type_t ;

/* Variables and functions */
 scalar_t__ DMU_META_DNODE_OBJECT ; 
 int DNODE_MIN_SLOTS ; 
 int /*<<< orphan*/  DNODE_MUST_BE_ALLOCATED ; 
 int DNODE_SHIFT ; 
 int /*<<< orphan*/  EBADF ; 
 int /*<<< orphan*/  FTAG ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int dnode_hold_impl (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dnode_reallocate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dnode_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
dmu_object_reclaim_dnsize(objset_t *os, uint64_t object, dmu_object_type_t ot,
    int blocksize, dmu_object_type_t bonustype, int bonuslen, int dnodesize,
    dmu_tx_t *tx)
{
	dnode_t *dn;
	int dn_slots = dnodesize >> DNODE_SHIFT;
	int err;

	if (dn_slots == 0)
		dn_slots = DNODE_MIN_SLOTS;

	if (object == DMU_META_DNODE_OBJECT)
		return (SET_ERROR(EBADF));

	err = dnode_hold_impl(os, object, DNODE_MUST_BE_ALLOCATED, 0,
	    FTAG, &dn);
	if (err)
		return (err);

	dnode_reallocate(dn, ot, blocksize, bonustype, bonuslen, dn_slots, tx);

	dnode_rele(dn, FTAG);
	return (err);
}