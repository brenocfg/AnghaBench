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
typedef  TYPE_1__* if_softc_ctx_t ;
typedef  TYPE_2__* if_shared_ctx_t ;
typedef  TYPE_3__* if_ctx_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_5__ {scalar_t__ isc_ntxqsets; scalar_t__ isc_nrxqsets; scalar_t__* isc_ntxd; scalar_t__* isc_nrxd; } ;
struct TYPE_7__ {scalar_t__ ifc_sysctl_ntxqs; scalar_t__ ifc_sysctl_nrxqs; scalar_t__* ifc_sysctl_ntxds; scalar_t__* ifc_sysctl_nrxds; int /*<<< orphan*/  ifc_dev; TYPE_2__* ifc_sctx; TYPE_1__ ifc_softc_ctx; } ;
struct TYPE_6__ {int isc_ntxqs; scalar_t__* isc_ntxd_default; int isc_nrxqs; scalar_t__* isc_nrxd_default; scalar_t__* isc_nrxd_min; scalar_t__* isc_nrxd_max; scalar_t__* isc_ntxd_min; scalar_t__* isc_ntxd_max; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  powerof2 (scalar_t__) ; 

__attribute__((used)) static void
iflib_reset_qvalues(if_ctx_t ctx)
{
	if_softc_ctx_t scctx = &ctx->ifc_softc_ctx;
	if_shared_ctx_t sctx = ctx->ifc_sctx;
	device_t dev = ctx->ifc_dev;
	int i;

	if (ctx->ifc_sysctl_ntxqs != 0)
		scctx->isc_ntxqsets = ctx->ifc_sysctl_ntxqs;
	if (ctx->ifc_sysctl_nrxqs != 0)
		scctx->isc_nrxqsets = ctx->ifc_sysctl_nrxqs;

	for (i = 0; i < sctx->isc_ntxqs; i++) {
		if (ctx->ifc_sysctl_ntxds[i] != 0)
			scctx->isc_ntxd[i] = ctx->ifc_sysctl_ntxds[i];
		else
			scctx->isc_ntxd[i] = sctx->isc_ntxd_default[i];
	}

	for (i = 0; i < sctx->isc_nrxqs; i++) {
		if (ctx->ifc_sysctl_nrxds[i] != 0)
			scctx->isc_nrxd[i] = ctx->ifc_sysctl_nrxds[i];
		else
			scctx->isc_nrxd[i] = sctx->isc_nrxd_default[i];
	}

	for (i = 0; i < sctx->isc_nrxqs; i++) {
		if (scctx->isc_nrxd[i] < sctx->isc_nrxd_min[i]) {
			device_printf(dev, "nrxd%d: %d less than nrxd_min %d - resetting to min\n",
				      i, scctx->isc_nrxd[i], sctx->isc_nrxd_min[i]);
			scctx->isc_nrxd[i] = sctx->isc_nrxd_min[i];
		}
		if (scctx->isc_nrxd[i] > sctx->isc_nrxd_max[i]) {
			device_printf(dev, "nrxd%d: %d greater than nrxd_max %d - resetting to max\n",
				      i, scctx->isc_nrxd[i], sctx->isc_nrxd_max[i]);
			scctx->isc_nrxd[i] = sctx->isc_nrxd_max[i];
		}
		if (!powerof2(scctx->isc_nrxd[i])) {
			device_printf(dev, "nrxd%d: %d is not a power of 2 - using default value of %d\n",
				      i, scctx->isc_nrxd[i], sctx->isc_nrxd_default[i]);
			scctx->isc_nrxd[i] = sctx->isc_nrxd_default[i];
		}
	}

	for (i = 0; i < sctx->isc_ntxqs; i++) {
		if (scctx->isc_ntxd[i] < sctx->isc_ntxd_min[i]) {
			device_printf(dev, "ntxd%d: %d less than ntxd_min %d - resetting to min\n",
				      i, scctx->isc_ntxd[i], sctx->isc_ntxd_min[i]);
			scctx->isc_ntxd[i] = sctx->isc_ntxd_min[i];
		}
		if (scctx->isc_ntxd[i] > sctx->isc_ntxd_max[i]) {
			device_printf(dev, "ntxd%d: %d greater than ntxd_max %d - resetting to max\n",
				      i, scctx->isc_ntxd[i], sctx->isc_ntxd_max[i]);
			scctx->isc_ntxd[i] = sctx->isc_ntxd_max[i];
		}
		if (!powerof2(scctx->isc_ntxd[i])) {
			device_printf(dev, "ntxd%d: %d is not a power of 2 - using default value of %d\n",
				      i, scctx->isc_ntxd[i], sctx->isc_ntxd_default[i]);
			scctx->isc_ntxd[i] = sctx->isc_ntxd_default[i];
		}
	}
}