#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  iflib_txq_t ;
typedef  TYPE_1__* if_ctx_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_8__ {int /*<<< orphan*/  ifc_txqs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTX_LOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  CTX_UNLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  IFDI_RESUME (TYPE_1__*) ; 
 int /*<<< orphan*/  IFLIB_RESTART_BUDGET ; 
 int NTXQSETS (TYPE_1__*) ; 
 int bus_generic_resume (int /*<<< orphan*/ ) ; 
 TYPE_1__* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iflib_if_init_locked (TYPE_1__*) ; 
 int /*<<< orphan*/  iflib_txq_check_drain (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
iflib_device_resume(device_t dev)
{
	if_ctx_t ctx = device_get_softc(dev);
	iflib_txq_t txq = ctx->ifc_txqs;

	CTX_LOCK(ctx);
	IFDI_RESUME(ctx);
	iflib_if_init_locked(ctx);
	CTX_UNLOCK(ctx);
	for (int i = 0; i < NTXQSETS(ctx); i++, txq++)
		iflib_txq_check_drain(txq, IFLIB_RESTART_BUDGET);

	return (bus_generic_resume(dev));
}