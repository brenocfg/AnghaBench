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
typedef  scalar_t__ uint32_t ;
struct vlapic {int /*<<< orphan*/  callout; int /*<<< orphan*/  timer_period_bt; int /*<<< orphan*/  timer_fire_bt; int /*<<< orphan*/  timer_freq_bt; struct LAPIC* apic_page; } ;
struct LAPIC {scalar_t__ icr_timer; } ;
typedef  int /*<<< orphan*/  sbintime_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLAPIC_TIMER_LOCK (struct vlapic*) ; 
 int /*<<< orphan*/  VLAPIC_TIMER_UNLOCK (struct vlapic*) ; 
 int /*<<< orphan*/  bintime_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bintime_mul (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  binuptime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bttosbt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_reset_sbt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vlapic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlapic_callout_handler ; 

void
vlapic_icrtmr_write_handler(struct vlapic *vlapic)
{
	struct LAPIC *lapic;
	sbintime_t sbt;
	uint32_t icr_timer;

	VLAPIC_TIMER_LOCK(vlapic);

	lapic = vlapic->apic_page;
	icr_timer = lapic->icr_timer;

	vlapic->timer_period_bt = vlapic->timer_freq_bt;
	bintime_mul(&vlapic->timer_period_bt, icr_timer);

	if (icr_timer != 0) {
		binuptime(&vlapic->timer_fire_bt);
		bintime_add(&vlapic->timer_fire_bt, &vlapic->timer_period_bt);

		sbt = bttosbt(vlapic->timer_period_bt);
		callout_reset_sbt(&vlapic->callout, sbt, 0,
		    vlapic_callout_handler, vlapic, 0);
	} else
		callout_stop(&vlapic->callout);

	VLAPIC_TIMER_UNLOCK(vlapic);
}