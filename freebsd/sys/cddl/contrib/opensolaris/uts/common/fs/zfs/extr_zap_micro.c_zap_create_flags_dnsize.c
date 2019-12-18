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
typedef  int /*<<< orphan*/  zap_flags_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
typedef  int /*<<< orphan*/  dmu_object_type_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int SPA_MINBLOCKSHIFT ; 
 int SPA_OLD_MAXBLOCKSHIFT ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  dmu_object_alloc_dnsize (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ dmu_object_set_blocksize (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long long,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mzap_create_impl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

uint64_t
zap_create_flags_dnsize(objset_t *os, int normflags, zap_flags_t flags,
    dmu_object_type_t ot, int leaf_blockshift, int indirect_blockshift,
    dmu_object_type_t bonustype, int bonuslen, int dnodesize, dmu_tx_t *tx)
{
	uint64_t obj = dmu_object_alloc_dnsize(os, ot, 0, bonustype, bonuslen,
	    dnodesize, tx);

	ASSERT(leaf_blockshift >= SPA_MINBLOCKSHIFT &&
	    leaf_blockshift <= SPA_OLD_MAXBLOCKSHIFT &&
	    indirect_blockshift >= SPA_MINBLOCKSHIFT &&
	    indirect_blockshift <= SPA_OLD_MAXBLOCKSHIFT);

	VERIFY(dmu_object_set_blocksize(os, obj,
	    1ULL << leaf_blockshift, indirect_blockshift, tx) == 0);

	mzap_create_impl(os, obj, normflags, flags, tx);
	return (obj);
}