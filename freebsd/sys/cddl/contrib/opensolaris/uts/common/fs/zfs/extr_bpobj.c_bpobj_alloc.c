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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
typedef  int /*<<< orphan*/  bpobj_phys_t ;

/* Variables and functions */
 int BPOBJ_SIZE_V0 ; 
 int BPOBJ_SIZE_V1 ; 
 int /*<<< orphan*/  DMU_OT_BPOBJ ; 
 int /*<<< orphan*/  DMU_OT_BPOBJ_HDR ; 
 scalar_t__ SPA_VERSION_BPOBJ_ACCOUNT ; 
 scalar_t__ SPA_VERSION_DEADLISTS ; 
 int /*<<< orphan*/  dmu_object_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_objset_spa (int /*<<< orphan*/ *) ; 
 scalar_t__ spa_version (int /*<<< orphan*/ ) ; 

uint64_t
bpobj_alloc(objset_t *os, int blocksize, dmu_tx_t *tx)
{
	int size;

	if (spa_version(dmu_objset_spa(os)) < SPA_VERSION_BPOBJ_ACCOUNT)
		size = BPOBJ_SIZE_V0;
	else if (spa_version(dmu_objset_spa(os)) < SPA_VERSION_DEADLISTS)
		size = BPOBJ_SIZE_V1;
	else
		size = sizeof (bpobj_phys_t);

	return (dmu_object_alloc(os, DMU_OT_BPOBJ, blocksize,
	    DMU_OT_BPOBJ_HDR, size, tx));
}