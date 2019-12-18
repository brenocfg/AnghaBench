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
struct aac_softc {int aac_state; int flags; scalar_t__ aac_sync_cm; } ;
struct aac_command {int cm_flags; scalar_t__ cm_datalen; } ;

/* Variables and functions */
 int AAC_CMD_MAPPED ; 
 int AAC_FLAGS_SYNC_MODE ; 
 int AAC_QUEUE_FRZN ; 
 int AAC_STATE_RESET ; 
 char* HBA_FLAGS_DBG_ERROR_B ; 
 char* HBA_FLAGS_DBG_FUNCTION_ENTRY_B ; 
 struct aac_command* aac_dequeue_ready (struct aac_softc*) ; 
 int /*<<< orphan*/  aac_load_map_command_sg (struct aac_softc*,struct aac_command*) ; 
 int /*<<< orphan*/  aacraid_map_command_sg (struct aac_command*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwprintf (struct aac_softc*,char*,char*) ; 
 int /*<<< orphan*/  panic (char*,struct aac_command*) ; 

void
aacraid_startio(struct aac_softc *sc)
{
	struct aac_command *cm;

	fwprintf(sc, HBA_FLAGS_DBG_FUNCTION_ENTRY_B, "");

	for (;;) {
		if (sc->aac_state & AAC_STATE_RESET) {
			fwprintf(sc, HBA_FLAGS_DBG_ERROR_B, "AAC_STATE_RESET");
			break;
		}
		/*
		 * This flag might be set if the card is out of resources.
		 * Checking it here prevents an infinite loop of deferrals.
		 */
		if (sc->flags & AAC_QUEUE_FRZN) {
			fwprintf(sc, HBA_FLAGS_DBG_ERROR_B, "AAC_QUEUE_FRZN");
			break;
		}

		/*
		 * Try to get a command that's been put off for lack of
		 * resources
		 */
		if ((sc->flags & AAC_FLAGS_SYNC_MODE) && sc->aac_sync_cm)
			break;
		cm = aac_dequeue_ready(sc);

		/* nothing to do? */
		if (cm == NULL)
			break;

		/* don't map more than once */
		if (cm->cm_flags & AAC_CMD_MAPPED)
			panic("aac: command %p already mapped", cm);

		/*
		 * Set up the command to go to the controller.  If there are no
		 * data buffers associated with the command then it can bypass
		 * busdma.
		 */
		if (cm->cm_datalen)
			aac_load_map_command_sg(sc, cm);
		else
			aacraid_map_command_sg(cm, NULL, 0, 0);
	}
}