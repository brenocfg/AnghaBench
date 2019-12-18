#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vmxnet3_softc {int /*<<< orphan*/  vmx_media; int /*<<< orphan*/  vmx_flags; } ;
typedef  TYPE_1__* if_softc_ctx_t ;
typedef  int /*<<< orphan*/  if_ctx_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_3__ {int isc_nrxqsets; } ;

/* Variables and functions */
 int IFM_AUTO ; 
 int IFM_ETHER ; 
 int /*<<< orphan*/  VMXNET3_FLAG_RSS ; 
 int /*<<< orphan*/  iflib_get_dev (int /*<<< orphan*/ ) ; 
 struct vmxnet3_softc* iflib_get_softc (int /*<<< orphan*/ ) ; 
 TYPE_1__* iflib_get_softc_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifmedia_add (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ifmedia_set (int /*<<< orphan*/ ,int) ; 
 int vmxnet3_alloc_data (struct vmxnet3_softc*) ; 
 int /*<<< orphan*/  vmxnet3_set_interrupt_idx (struct vmxnet3_softc*) ; 
 int /*<<< orphan*/  vmxnet3_setup_sysctl (struct vmxnet3_softc*) ; 

__attribute__((used)) static int
vmxnet3_attach_post(if_ctx_t ctx)
{
	device_t dev;
	if_softc_ctx_t scctx;
	struct vmxnet3_softc *sc;
	int error;

	dev = iflib_get_dev(ctx);
	scctx = iflib_get_softc_ctx(ctx);
	sc = iflib_get_softc(ctx);

	if (scctx->isc_nrxqsets > 1)
		sc->vmx_flags |= VMXNET3_FLAG_RSS;

	error = vmxnet3_alloc_data(sc);
	if (error)
		goto fail;

	vmxnet3_set_interrupt_idx(sc);
	vmxnet3_setup_sysctl(sc);

	ifmedia_add(sc->vmx_media, IFM_ETHER | IFM_AUTO, 0, NULL);
	ifmedia_set(sc->vmx_media, IFM_ETHER | IFM_AUTO);

fail:
	return (error);
}