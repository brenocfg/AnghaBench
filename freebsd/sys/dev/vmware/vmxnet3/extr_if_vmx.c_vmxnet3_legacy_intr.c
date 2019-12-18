#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vmxnet3_softc {scalar_t__ vmx_intr_mask_mode; TYPE_1__* vmx_ds; int /*<<< orphan*/  vmx_ctx; TYPE_2__* vmx_scctx; } ;
typedef  TYPE_2__* if_softc_ctx_t ;
typedef  int /*<<< orphan*/  if_ctx_t ;
struct TYPE_4__ {scalar_t__ isc_intr; } ;
struct TYPE_3__ {scalar_t__ event; } ;

/* Variables and functions */
 int FILTER_HANDLED ; 
 int FILTER_SCHEDULE_THREAD ; 
 scalar_t__ IFLIB_INTR_LEGACY ; 
 int /*<<< orphan*/  VMXNET3_BAR1_INTR ; 
 scalar_t__ VMXNET3_IMM_ACTIVE ; 
 int /*<<< orphan*/  iflib_admin_intr_deferred (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmxnet3_intr_disable_all (int /*<<< orphan*/ ) ; 
 scalar_t__ vmxnet3_read_bar1 (struct vmxnet3_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vmxnet3_legacy_intr(void *xsc)
{
	struct vmxnet3_softc *sc;
	if_softc_ctx_t scctx;
	if_ctx_t ctx;
	
	sc = xsc;
	scctx = sc->vmx_scctx;
	ctx = sc->vmx_ctx;

	/*
	 * When there is only a single interrupt configured, this routine
	 * runs in fast interrupt context, following which the rxq 0 task
	 * will be enqueued.
	 */
	if (scctx->isc_intr == IFLIB_INTR_LEGACY) {
		if (vmxnet3_read_bar1(sc, VMXNET3_BAR1_INTR) == 0)
			return (FILTER_HANDLED);
	}
	if (sc->vmx_intr_mask_mode == VMXNET3_IMM_ACTIVE)
		vmxnet3_intr_disable_all(ctx);

	if (sc->vmx_ds->event != 0)
		iflib_admin_intr_deferred(ctx);

	/*
	 * XXX - When there is both rxq and event activity, do we care
	 * whether the rxq 0 task or the admin task re-enables the interrupt
	 * first?
	 */
	return (FILTER_SCHEDULE_THREAD);
}