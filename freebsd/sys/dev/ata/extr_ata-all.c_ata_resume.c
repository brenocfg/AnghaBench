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
struct ata_channel {int flags; int /*<<< orphan*/  poll_callout; int /*<<< orphan*/  state_mtx; int /*<<< orphan*/  sim; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ATA_PERIODIC_POLL ; 
 int ENXIO ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ata_periodic_poll ; 
 int ata_reinit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ata_channel*) ; 
 struct ata_channel* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpt_release_simq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
ata_resume(device_t dev)
{
    struct ata_channel *ch;
    int error;

    /* check for valid device */
    if (!dev || !(ch = device_get_softc(dev)))
	return ENXIO;

	mtx_lock(&ch->state_mtx);
	error = ata_reinit(dev);
	xpt_release_simq(ch->sim, TRUE);
	mtx_unlock(&ch->state_mtx);
	if (ch->flags & ATA_PERIODIC_POLL)
		callout_reset(&ch->poll_callout, hz, ata_periodic_poll, ch);
    return error;
}