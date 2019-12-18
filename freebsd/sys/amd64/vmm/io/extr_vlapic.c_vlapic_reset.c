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
struct vlapic {scalar_t__ vcpuid; int /*<<< orphan*/  svr_last; int /*<<< orphan*/  boot_state; struct LAPIC* apic_page; } ;
struct LAPIC {int version; int dfr; int /*<<< orphan*/  svr; scalar_t__ dcr_timer; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  APIC_SVR_VECTOR ; 
 int /*<<< orphan*/  BS_INIT ; 
 int /*<<< orphan*/  BS_RUNNING ; 
 int MAXLVTSHIFT ; 
 int VLAPIC_MAXLVT_INDEX ; 
 int VLAPIC_VERSION ; 
 int /*<<< orphan*/  bzero (struct LAPIC*,int) ; 
 int /*<<< orphan*/  vlapic_dcr_write_handler (struct vlapic*) ; 
 int /*<<< orphan*/  vlapic_get_id (struct vlapic*) ; 
 int /*<<< orphan*/  vlapic_mask_lvts (struct vlapic*) ; 
 int /*<<< orphan*/  vlapic_reset_tmr (struct vlapic*) ; 

__attribute__((used)) static void
vlapic_reset(struct vlapic *vlapic)
{
	struct LAPIC *lapic;
	
	lapic = vlapic->apic_page;
	bzero(lapic, sizeof(struct LAPIC));

	lapic->id = vlapic_get_id(vlapic);
	lapic->version = VLAPIC_VERSION;
	lapic->version |= (VLAPIC_MAXLVT_INDEX << MAXLVTSHIFT);
	lapic->dfr = 0xffffffff;
	lapic->svr = APIC_SVR_VECTOR;
	vlapic_mask_lvts(vlapic);
	vlapic_reset_tmr(vlapic);

	lapic->dcr_timer = 0;
	vlapic_dcr_write_handler(vlapic);

	if (vlapic->vcpuid == 0)
		vlapic->boot_state = BS_RUNNING;	/* BSP */
	else
		vlapic->boot_state = BS_INIT;		/* AP */

	vlapic->svr_last = lapic->svr;
}