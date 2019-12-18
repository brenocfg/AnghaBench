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
struct siis_channel {int /*<<< orphan*/  r_mem; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_OUTL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIIS_P_CTLSET ; 
 int /*<<< orphan*/  SIIS_P_CTL_PORT_RESET ; 
 struct siis_channel* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
siis_ch_deinit(device_t dev)
{
	struct siis_channel *ch = device_get_softc(dev);

	/* Put port into reset state. */
	ATA_OUTL(ch->r_mem, SIIS_P_CTLSET, SIIS_P_CTL_PORT_RESET);
	return (0);
}