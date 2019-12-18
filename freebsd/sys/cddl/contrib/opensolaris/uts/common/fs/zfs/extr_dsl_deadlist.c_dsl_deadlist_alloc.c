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
typedef  int /*<<< orphan*/  dsl_deadlist_phys_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMU_OT_DEADLIST ; 
 int /*<<< orphan*/  DMU_OT_DEADLIST_HDR ; 
 int /*<<< orphan*/  SPA_OLD_MAXBLOCKSIZE ; 
 scalar_t__ SPA_VERSION_DEADLISTS ; 
 int /*<<< orphan*/  bpobj_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_objset_spa (int /*<<< orphan*/ *) ; 
 scalar_t__ spa_version (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zap_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

uint64_t
dsl_deadlist_alloc(objset_t *os, dmu_tx_t *tx)
{
	if (spa_version(dmu_objset_spa(os)) < SPA_VERSION_DEADLISTS)
		return (bpobj_alloc(os, SPA_OLD_MAXBLOCKSIZE, tx));
	return (zap_create(os, DMU_OT_DEADLIST, DMU_OT_DEADLIST_HDR,
	    sizeof (dsl_deadlist_phys_t), tx));
}