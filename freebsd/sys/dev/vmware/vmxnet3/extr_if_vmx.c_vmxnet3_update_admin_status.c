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
struct TYPE_2__ {scalar_t__ event; } ;

/* Variables and functions */
 struct vmxnet3_softc* iflib_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmxnet3_evintr (struct vmxnet3_softc*) ; 
 int /*<<< orphan*/  vmxnet3_refresh_host_stats (struct vmxnet3_softc*) ; 

__attribute__((used)) static void
vmxnet3_update_admin_status(if_ctx_t ctx)
{
	struct vmxnet3_softc *sc;

	sc = iflib_get_softc(ctx);
	if (sc->vmx_ds->event != 0)
		vmxnet3_evintr(sc);

	vmxnet3_refresh_host_stats(sc);
}