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
struct bio {int dummy; } ;
struct aac_softc {int flags; int /*<<< orphan*/  aac_buffer_dmat; } ;
struct aac_command {int cm_flags; scalar_t__ cm_datalen; int /*<<< orphan*/  cm_data; int /*<<< orphan*/  cm_datamap; scalar_t__ cm_private; } ;

/* Variables and functions */
 int AAC_CMD_MAPPED ; 
 int AAC_QUEUE_FRZN ; 
 int AAC_REQ_BIO ; 
 int EINPROGRESS ; 
 char* HBA_FLAGS_DBG_COMM_B ; 
 char* HBA_FLAGS_DBG_FUNCTION_ENTRY_B ; 
 int /*<<< orphan*/  aac_bio_command (struct aac_softc*,struct aac_command**) ; 
 struct aac_command* aac_dequeue_ready (struct aac_softc*) ; 
 int /*<<< orphan*/  aac_map_command_sg (struct aac_command*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/  (*) (struct aac_command*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ),struct aac_command*,int /*<<< orphan*/ ) ; 
 int bus_dmamap_load_bio (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bio*,int /*<<< orphan*/  (*) (struct aac_command*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ),struct aac_command*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwprintf (struct aac_softc*,char*,char*) ; 
 int /*<<< orphan*/  panic (char*,...) ; 

void
aac_startio(struct aac_softc *sc)
{
	struct aac_command *cm;
	int error;

	fwprintf(sc, HBA_FLAGS_DBG_FUNCTION_ENTRY_B, "");

	for (;;) {
		/*
		 * This flag might be set if the card is out of resources.
		 * Checking it here prevents an infinite loop of deferrals.
		 */
		if (sc->flags & AAC_QUEUE_FRZN)
			break;

		/*
		 * Try to get a command that's been put off for lack of
		 * resources
		 */
		cm = aac_dequeue_ready(sc);

		/*
		 * Try to build a command off the bio queue (ignore error
		 * return)
		 */
		if (cm == NULL)
			aac_bio_command(sc, &cm);

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
		if (cm->cm_datalen != 0) {
			if (cm->cm_flags & AAC_REQ_BIO)
				error = bus_dmamap_load_bio(
				    sc->aac_buffer_dmat, cm->cm_datamap,
				    (struct bio *)cm->cm_private,
				    aac_map_command_sg, cm, 0);
			else
				error = bus_dmamap_load(sc->aac_buffer_dmat,
				    cm->cm_datamap, cm->cm_data,
				    cm->cm_datalen, aac_map_command_sg, cm, 0);
			if (error == EINPROGRESS) {
				fwprintf(sc, HBA_FLAGS_DBG_COMM_B, "freezing queue\n");
				sc->flags |= AAC_QUEUE_FRZN;
			} else if (error != 0)
				panic("aac_startio: unexpected error %d from "
				      "busdma", error);
		} else
			aac_map_command_sg(cm, NULL, 0, 0);
	}
}