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
struct bge_softc {int bge_mfw_flags; } ;

/* Variables and functions */
 int APE_READ_4 (struct bge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  APE_WRITE_4 (struct bge_softc*,int /*<<< orphan*/ ,int) ; 
 int BGE_APE_EVENT_STATUS_DRIVER_EVNT ; 
 int BGE_APE_EVENT_STATUS_STATE_CHNGE ; 
 int BGE_APE_EVENT_STATUS_STATE_START ; 
 int BGE_APE_EVENT_STATUS_STATE_SUSPEND ; 
 int BGE_APE_EVENT_STATUS_STATE_UNLOAD ; 
 int /*<<< orphan*/  BGE_APE_HOST_BEHAVIOR ; 
 int BGE_APE_HOST_BEHAV_NO_PHYLOCK ; 
 int /*<<< orphan*/  BGE_APE_HOST_DRIVER_ID ; 
 int BGE_APE_HOST_DRIVER_ID_MAGIC (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BGE_APE_HOST_DRVR_STATE ; 
 int BGE_APE_HOST_DRVR_STATE_START ; 
 int BGE_APE_HOST_DRVR_STATE_UNLOAD ; 
 int BGE_APE_HOST_HEARTBEAT_INT_DISABLE ; 
 int /*<<< orphan*/  BGE_APE_HOST_HEARTBEAT_INT_MS ; 
 int /*<<< orphan*/  BGE_APE_HOST_INIT_COUNT ; 
 int /*<<< orphan*/  BGE_APE_HOST_SEG_LEN ; 
 int BGE_APE_HOST_SEG_LEN_MAGIC ; 
 int /*<<< orphan*/  BGE_APE_HOST_SEG_SIG ; 
 int BGE_APE_HOST_SEG_SIG_MAGIC ; 
 int BGE_MFW_ON_APE ; 
#define  BGE_RESET_SHUTDOWN 130 
#define  BGE_RESET_START 129 
#define  BGE_RESET_SUSPEND 128 
 int /*<<< orphan*/  bge_ape_send_event (struct bge_softc*,int) ; 

__attribute__((used)) static void
bge_ape_driver_state_change(struct bge_softc *sc, int kind)
{
	uint32_t apedata, event;

	if ((sc->bge_mfw_flags & BGE_MFW_ON_APE) == 0)
		return;

	switch (kind) {
	case BGE_RESET_START:
		/* If this is the first load, clear the load counter. */
		apedata = APE_READ_4(sc, BGE_APE_HOST_SEG_SIG);
		if (apedata != BGE_APE_HOST_SEG_SIG_MAGIC)
			APE_WRITE_4(sc, BGE_APE_HOST_INIT_COUNT, 0);
		else {
			apedata = APE_READ_4(sc, BGE_APE_HOST_INIT_COUNT);
			APE_WRITE_4(sc, BGE_APE_HOST_INIT_COUNT, ++apedata);
		}
		APE_WRITE_4(sc, BGE_APE_HOST_SEG_SIG,
		    BGE_APE_HOST_SEG_SIG_MAGIC);
		APE_WRITE_4(sc, BGE_APE_HOST_SEG_LEN,
		    BGE_APE_HOST_SEG_LEN_MAGIC);

		/* Add some version info if bge(4) supports it. */
		APE_WRITE_4(sc, BGE_APE_HOST_DRIVER_ID,
		    BGE_APE_HOST_DRIVER_ID_MAGIC(1, 0));
		APE_WRITE_4(sc, BGE_APE_HOST_BEHAVIOR,
		    BGE_APE_HOST_BEHAV_NO_PHYLOCK);
		APE_WRITE_4(sc, BGE_APE_HOST_HEARTBEAT_INT_MS,
		    BGE_APE_HOST_HEARTBEAT_INT_DISABLE);
		APE_WRITE_4(sc, BGE_APE_HOST_DRVR_STATE,
		    BGE_APE_HOST_DRVR_STATE_START);
		event = BGE_APE_EVENT_STATUS_STATE_START;
		break;
	case BGE_RESET_SHUTDOWN:
		APE_WRITE_4(sc, BGE_APE_HOST_DRVR_STATE,
		    BGE_APE_HOST_DRVR_STATE_UNLOAD);
		event = BGE_APE_EVENT_STATUS_STATE_UNLOAD;
		break;
	case BGE_RESET_SUSPEND:
		event = BGE_APE_EVENT_STATUS_STATE_SUSPEND;
		break;
	default:
		return;
	}

	bge_ape_send_event(sc, event | BGE_APE_EVENT_STATUS_DRIVER_EVNT |
	    BGE_APE_EVENT_STATUS_STATE_CHNGE);
}