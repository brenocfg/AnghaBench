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
typedef  int uint8_t ;
struct mvs_channel {scalar_t__ fake_busy; int /*<<< orphan*/  r_mem; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_ALTSTAT ; 
 int ATA_INB (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATA_STATUS ; 
 int ATA_S_BUSY ; 
 int ATA_S_DRQ ; 
 int ATA_S_ERROR ; 
 struct mvs_channel* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint8_t
mvs_getstatus(device_t dev, int clear)
{
	struct mvs_channel *ch = device_get_softc(dev);
	uint8_t status = ATA_INB(ch->r_mem, clear ? ATA_STATUS : ATA_ALTSTAT);

	if (ch->fake_busy) {
		if (status & (ATA_S_BUSY | ATA_S_DRQ | ATA_S_ERROR))
			ch->fake_busy = 0;
		else
			status |= ATA_S_BUSY;
	}
	return (status);
}