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
typedef  int zap_flags_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMU_OT_DDT_ZAP ; 
 int /*<<< orphan*/  DMU_OT_NONE ; 
 int ENOTSUP ; 
 int ZAP_FLAG_HASH64 ; 
 int ZAP_FLAG_PRE_HASHED_KEY ; 
 int ZAP_FLAG_UINT64_KEY ; 
 int /*<<< orphan*/  ddt_zap_indirect_blockshift ; 
 int /*<<< orphan*/  ddt_zap_leaf_blockshift ; 
 scalar_t__ zap_create_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ddt_zap_create(objset_t *os, uint64_t *objectp, dmu_tx_t *tx, boolean_t prehash)
{
	zap_flags_t flags = ZAP_FLAG_HASH64 | ZAP_FLAG_UINT64_KEY;

	if (prehash)
		flags |= ZAP_FLAG_PRE_HASHED_KEY;

	*objectp = zap_create_flags(os, 0, flags, DMU_OT_DDT_ZAP,
	    ddt_zap_leaf_blockshift, ddt_zap_indirect_blockshift,
	    DMU_OT_NONE, 0, tx);

	return (*objectp == 0 ? ENOTSUP : 0);
}