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
struct ata_channel {int flags; scalar_t__ state; int /*<<< orphan*/  state_mtx; int /*<<< orphan*/  sim; int /*<<< orphan*/  poll_callout; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ ATA_IDLE ; 
 int ATA_PERIODIC_POLL ; 
 int ENXIO ; 
 int /*<<< orphan*/  PRIBIO ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 struct ata_channel* device_get_softc (int /*<<< orphan*/ ) ; 
 int hz ; 
 int /*<<< orphan*/  msleep (struct ata_channel*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpt_freeze_simq (int /*<<< orphan*/ ,int) ; 

int
ata_suspend(device_t dev)
{
    struct ata_channel *ch;

    /* check for valid device */
    if (!dev || !(ch = device_get_softc(dev)))
	return ENXIO;

    if (ch->flags & ATA_PERIODIC_POLL)
	callout_drain(&ch->poll_callout);
    mtx_lock(&ch->state_mtx);
    xpt_freeze_simq(ch->sim, 1);
    while (ch->state != ATA_IDLE)
	msleep(ch, &ch->state_mtx, PRIBIO, "atasusp", hz/100);
    mtx_unlock(&ch->state_mtx);
    return(0);
}