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
typedef  int /*<<< orphan*/  dmu_object_type_t ;

/* Variables and functions */
 int dmu_object_claim_dnsize (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mzap_create_impl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
zap_create_claim_norm_dnsize(objset_t *os, uint64_t obj, int normflags,
    dmu_object_type_t ot, dmu_object_type_t bonustype, int bonuslen,
    int dnodesize, dmu_tx_t *tx)
{
	int err;

	err = dmu_object_claim_dnsize(os, obj, ot, 0, bonustype, bonuslen,
	    dnodesize, tx);
	if (err != 0)
		return (err);
	mzap_create_impl(os, obj, normflags, 0, tx);
	return (0);
}