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
struct vmxnet3_softc {scalar_t__ vmx_intr_mask_mode; int /*<<< orphan*/  vmx_event_intr_idx; } ;

/* Variables and functions */
 int FILTER_SCHEDULE_THREAD ; 
 scalar_t__ VMXNET3_IMM_ACTIVE ; 
 int /*<<< orphan*/  vmxnet3_disable_intr (struct vmxnet3_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vmxnet3_event_intr(void *vsc)
{
	struct vmxnet3_softc *sc;

	sc = vsc;

	if (sc->vmx_intr_mask_mode == VMXNET3_IMM_ACTIVE)
		vmxnet3_disable_intr(sc, sc->vmx_event_intr_idx);

	/*
	 * The work will be done via vmxnet3_update_admin_status(), and the
	 * interrupt will be re-enabled in vmxnet3_link_intr_enable().
	 *
	 * The interrupt will be re-enabled by vmxnet3_link_intr_enable().
	 */
	return (FILTER_SCHEDULE_THREAD);
}