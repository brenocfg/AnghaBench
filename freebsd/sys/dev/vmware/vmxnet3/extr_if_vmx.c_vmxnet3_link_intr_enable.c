#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct vmxnet3_softc {int /*<<< orphan*/  vmx_event_intr_idx; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
 struct vmxnet3_softc* iflib_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmxnet3_enable_intr (struct vmxnet3_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vmxnet3_link_intr_enable(if_ctx_t ctx)
{
	struct vmxnet3_softc *sc;

	sc = iflib_get_softc(ctx);
	vmxnet3_enable_intr(sc, sc->vmx_event_intr_idx);
}