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
struct fsl_sata_channel {int /*<<< orphan*/  r_mem; } ;
struct cam_sim {int dummy; } ;

/* Variables and functions */
 scalar_t__ ATA_INL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FSL_SATA_P_HSTS ; 
 scalar_t__ cam_sim_softc (struct cam_sim*) ; 
 int /*<<< orphan*/  fsl_sata_intr_main (struct fsl_sata_channel*,scalar_t__) ; 

__attribute__((used)) static void
fsl_satapoll(struct cam_sim *sim)
{
	struct fsl_sata_channel *ch = (struct fsl_sata_channel *)cam_sim_softc(sim);
	uint32_t istatus;

	/* Read interrupt statuses and process if any. */
	istatus = ATA_INL(ch->r_mem, FSL_SATA_P_HSTS);
	if (istatus != 0)
		fsl_sata_intr_main(ch, istatus);
}