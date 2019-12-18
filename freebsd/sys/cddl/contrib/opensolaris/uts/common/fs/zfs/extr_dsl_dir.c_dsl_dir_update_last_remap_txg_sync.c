#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  last_remap_txg ;
struct TYPE_6__ {int /*<<< orphan*/  dd_object; TYPE_1__* dd_pool; } ;
typedef  TYPE_2__ dsl_dir_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_7__ {scalar_t__ ddlrta_txg; TYPE_2__* ddulrta_dd; } ;
typedef  TYPE_3__ ddulrt_arg_t ;
struct TYPE_5__ {int /*<<< orphan*/ * dp_meta_objset; } ;

/* Variables and functions */
 int /*<<< orphan*/  DD_FIELD_LAST_REMAP_TXG ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_dir_zapify (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ zap_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,scalar_t__*) ; 
 int /*<<< orphan*/  zap_update (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,scalar_t__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dsl_dir_update_last_remap_txg_sync(void *varg, dmu_tx_t *tx)
{
	ddulrt_arg_t *arg = varg;
	uint64_t last_remap_txg;
	dsl_dir_t *dd = arg->ddulrta_dd;
	objset_t *mos = dd->dd_pool->dp_meta_objset;

	dsl_dir_zapify(dd, tx);
	if (zap_lookup(mos, dd->dd_object, DD_FIELD_LAST_REMAP_TXG,
	    sizeof (last_remap_txg), 1, &last_remap_txg) != 0 ||
	    last_remap_txg < arg->ddlrta_txg) {
		VERIFY0(zap_update(mos, dd->dd_object, DD_FIELD_LAST_REMAP_TXG,
		    sizeof (arg->ddlrta_txg), 1, &arg->ddlrta_txg, tx));
	}
}