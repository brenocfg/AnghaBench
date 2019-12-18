#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ zv_sync_cnt; int /*<<< orphan*/ * zv_zilog; } ;
typedef  TYPE_1__ zvol_state_t ;
typedef  int /*<<< orphan*/  zilog_t ;
typedef  void* uint64_t ;
struct TYPE_8__ {void* lr_length; void* lr_offset; int /*<<< orphan*/  lr_foid; } ;
typedef  TYPE_2__ lr_truncate_t ;
struct TYPE_9__ {int itx_sync; int /*<<< orphan*/  itx_lr; } ;
typedef  TYPE_3__ itx_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  TX_TRUNCATE ; 
 int /*<<< orphan*/  ZVOL_OBJ ; 
 int /*<<< orphan*/  zil_itx_assign (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *) ; 
 TYPE_3__* zil_itx_create (int /*<<< orphan*/ ,int) ; 
 scalar_t__ zil_replaying (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
zvol_log_truncate(zvol_state_t *zv, dmu_tx_t *tx, uint64_t off, uint64_t len,
    boolean_t sync)
{
	itx_t *itx;
	lr_truncate_t *lr;
	zilog_t *zilog = zv->zv_zilog;

	if (zil_replaying(zilog, tx))
		return;

	itx = zil_itx_create(TX_TRUNCATE, sizeof (*lr));
	lr = (lr_truncate_t *)&itx->itx_lr;
	lr->lr_foid = ZVOL_OBJ;
	lr->lr_offset = off;
	lr->lr_length = len;

	itx->itx_sync = (sync || zv->zv_sync_cnt != 0);
	zil_itx_assign(zilog, itx, tx);
}