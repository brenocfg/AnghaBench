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
typedef  int uint32_t ;
struct bge_softc {int bge_mfw_flags; int /*<<< orphan*/  bge_dev; } ;

/* Variables and functions */
 int APE_READ_4 (struct bge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  APE_WRITE_4 (struct bge_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BGE_APE_EVENT ; 
 int BGE_APE_EVENT_1 ; 
 int /*<<< orphan*/  BGE_APE_EVENT_STATUS ; 
 int BGE_APE_EVENT_STATUS_EVENT_PENDING ; 
 int /*<<< orphan*/  BGE_APE_LOCK_MEM ; 
 int BGE_MFW_ON_APE ; 
 int /*<<< orphan*/  DELAY (int) ; 
 scalar_t__ bge_ape_lock (struct bge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bge_ape_unlock (struct bge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
bge_ape_send_event(struct bge_softc *sc, uint32_t event)
{
	uint32_t apedata;
	int i;

	/* NCSI does not support APE events. */
	if ((sc->bge_mfw_flags & BGE_MFW_ON_APE) == 0)
		return;

	/* Wait up to 1ms for APE to service previous event. */
	for (i = 10; i > 0; i--) {
		if (bge_ape_lock(sc, BGE_APE_LOCK_MEM) != 0)
			break;
		apedata = APE_READ_4(sc, BGE_APE_EVENT_STATUS);
		if ((apedata & BGE_APE_EVENT_STATUS_EVENT_PENDING) == 0) {
			APE_WRITE_4(sc, BGE_APE_EVENT_STATUS, event |
			    BGE_APE_EVENT_STATUS_EVENT_PENDING);
			bge_ape_unlock(sc, BGE_APE_LOCK_MEM);
			APE_WRITE_4(sc, BGE_APE_EVENT, BGE_APE_EVENT_1);
			break;
		}
		bge_ape_unlock(sc, BGE_APE_LOCK_MEM);
		DELAY(100);
	}
	if (i == 0)
		device_printf(sc->bge_dev, "APE event 0x%08x send timed out\n",
		    event);
}