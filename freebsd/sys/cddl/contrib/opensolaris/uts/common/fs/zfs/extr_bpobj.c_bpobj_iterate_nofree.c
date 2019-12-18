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
typedef  int /*<<< orphan*/  dmu_tx_t ;
typedef  int /*<<< orphan*/  bpobj_t ;
typedef  int /*<<< orphan*/  bpobj_itor_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int bpobj_iterate_impl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
bpobj_iterate_nofree(bpobj_t *bpo, bpobj_itor_t func, void *arg, dmu_tx_t *tx)
{
	return (bpobj_iterate_impl(bpo, func, arg, tx, B_FALSE));
}