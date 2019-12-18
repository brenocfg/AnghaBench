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
struct cam_sim {int dummy; } ;
struct ata_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ata_interrupt_locked (struct ata_channel*) ; 
 scalar_t__ cam_sim_softc (struct cam_sim*) ; 

__attribute__((used)) static void
atapoll(struct cam_sim *sim)
{
	struct ata_channel *ch = (struct ata_channel *)cam_sim_softc(sim);

	ata_interrupt_locked(ch);
}