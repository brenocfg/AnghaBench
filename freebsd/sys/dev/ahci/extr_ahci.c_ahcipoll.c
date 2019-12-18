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
struct cam_sim {int dummy; } ;
struct ahci_channel {scalar_t__ resetting; scalar_t__ resetpolldiv; int /*<<< orphan*/  reset_timer; int /*<<< orphan*/  r_mem; } ;

/* Variables and functions */
 int /*<<< orphan*/  AHCI_P_IS ; 
 scalar_t__ ATA_INL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahci_ch_intr_main (struct ahci_channel*,scalar_t__) ; 
 int /*<<< orphan*/  ahci_reset_to (struct ahci_channel*) ; 
 int /*<<< orphan*/  callout_pending (int /*<<< orphan*/ *) ; 
 scalar_t__ cam_sim_softc (struct cam_sim*) ; 

__attribute__((used)) static void
ahcipoll(struct cam_sim *sim)
{
	struct ahci_channel *ch = (struct ahci_channel *)cam_sim_softc(sim);
	uint32_t istatus;

	/* Read interrupt statuses and process if any. */
	istatus = ATA_INL(ch->r_mem, AHCI_P_IS);
	if (istatus != 0)
		ahci_ch_intr_main(ch, istatus);
	if (ch->resetting != 0 &&
	    (--ch->resetpolldiv <= 0 || !callout_pending(&ch->reset_timer))) {
		ch->resetpolldiv = 1000;
		ahci_reset_to(ch);
	}
}