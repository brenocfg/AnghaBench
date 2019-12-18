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
struct vmxnet3_softc {TYPE_1__* vmx_ds; TYPE_2__* vmx_scctx; } ;
typedef  TYPE_2__* if_softc_ctx_t ;
typedef  int /*<<< orphan*/  if_ctx_t ;
struct TYPE_4__ {int isc_vectors; } ;
struct TYPE_3__ {int /*<<< orphan*/  ictrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMXNET3_ICTRL_DISABLE_ALL ; 
 struct vmxnet3_softc* iflib_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmxnet3_enable_intr (struct vmxnet3_softc*,int) ; 

__attribute__((used)) static void
vmxnet3_intr_enable_all(if_ctx_t ctx)
{
	struct vmxnet3_softc *sc;
	if_softc_ctx_t scctx;
	int i;

	sc = iflib_get_softc(ctx);
	scctx = sc->vmx_scctx;
	sc->vmx_ds->ictrl &= ~VMXNET3_ICTRL_DISABLE_ALL;
	for (i = 0; i < scctx->isc_vectors; i++)
		vmxnet3_enable_intr(sc, i);
}