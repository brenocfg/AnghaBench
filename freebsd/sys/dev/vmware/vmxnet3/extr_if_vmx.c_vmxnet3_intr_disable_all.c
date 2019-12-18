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
struct vmxnet3_softc {TYPE_1__* vmx_ds; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;
struct TYPE_2__ {int /*<<< orphan*/  ictrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMXNET3_ICTRL_DISABLE_ALL ; 
 int VMXNET3_MAX_INTRS ; 
 struct vmxnet3_softc* iflib_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmxnet3_disable_intr (struct vmxnet3_softc*,int) ; 

__attribute__((used)) static void
vmxnet3_intr_disable_all(if_ctx_t ctx)
{
	struct vmxnet3_softc *sc;
	int i;

	sc = iflib_get_softc(ctx);
	/*
	 * iflib may invoke this routine before vmxnet3_attach_post() has
	 * run, which is before the top level shared data area is
	 * initialized and the device made aware of it.
	 */
	if (sc->vmx_ds != NULL)
		sc->vmx_ds->ictrl |= VMXNET3_ICTRL_DISABLE_ALL;
	for (i = 0; i < VMXNET3_MAX_INTRS; i++)
		vmxnet3_disable_intr(sc, i);
}