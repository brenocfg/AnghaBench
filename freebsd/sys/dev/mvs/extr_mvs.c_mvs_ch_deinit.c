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
struct mvs_channel {int /*<<< orphan*/  r_mem; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_OUTL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EDMA_IEM ; 
 int /*<<< orphan*/  MVS_EDMA_OFF ; 
 struct mvs_channel* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvs_set_edma_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mvs_ch_deinit(device_t dev)
{
	struct mvs_channel *ch = device_get_softc(dev);

	/* Stop EDMA */
	mvs_set_edma_mode(dev, MVS_EDMA_OFF);
	/* Disable port interrupts. */
	ATA_OUTL(ch->r_mem, EDMA_IEM, 0);
	return (0);
}