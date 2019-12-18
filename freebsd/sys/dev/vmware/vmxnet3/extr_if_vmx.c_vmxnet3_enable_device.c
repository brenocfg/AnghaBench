#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vmxnet3_softc {int /*<<< orphan*/  vmx_dev; TYPE_1__* vmx_scctx; } ;
typedef  TYPE_1__* if_softc_ctx_t ;
struct TYPE_2__ {int isc_nrxqsets; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMXNET3_BAR0_RXH1 (int) ; 
 int /*<<< orphan*/  VMXNET3_BAR0_RXH2 (int) ; 
 int /*<<< orphan*/  VMXNET3_CMD_ENABLE ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ vmxnet3_read_cmd (struct vmxnet3_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmxnet3_write_bar0 (struct vmxnet3_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vmxnet3_enable_device(struct vmxnet3_softc *sc)
{
	if_softc_ctx_t scctx;
	int q;

	scctx = sc->vmx_scctx;

	if (vmxnet3_read_cmd(sc, VMXNET3_CMD_ENABLE) != 0) {
		device_printf(sc->vmx_dev, "device enable command failed!\n");
		return (1);
	}

	/* Reset the Rx queue heads. */
	for (q = 0; q < scctx->isc_nrxqsets; q++) {
		vmxnet3_write_bar0(sc, VMXNET3_BAR0_RXH1(q), 0);
		vmxnet3_write_bar0(sc, VMXNET3_BAR0_RXH2(q), 0);
	}

	return (0);
}