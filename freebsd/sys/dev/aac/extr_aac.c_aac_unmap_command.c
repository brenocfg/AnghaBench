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
struct aac_softc {int /*<<< orphan*/  aac_buffer_dmat; } ;
struct aac_command {int cm_flags; scalar_t__ cm_datalen; int /*<<< orphan*/  cm_datamap; struct aac_softc* cm_sc; } ;

/* Variables and functions */
 int AAC_CMD_DATAIN ; 
 int AAC_CMD_DATAOUT ; 
 int AAC_CMD_MAPPED ; 
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 char* HBA_FLAGS_DBG_FUNCTION_ENTRY_B ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwprintf (struct aac_softc*,char*,char*) ; 

__attribute__((used)) static void
aac_unmap_command(struct aac_command *cm)
{
	struct aac_softc *sc;

	sc = cm->cm_sc;
	fwprintf(sc, HBA_FLAGS_DBG_FUNCTION_ENTRY_B, "");

	if (!(cm->cm_flags & AAC_CMD_MAPPED))
		return;

	if (cm->cm_datalen != 0) {
		if (cm->cm_flags & AAC_CMD_DATAIN)
			bus_dmamap_sync(sc->aac_buffer_dmat, cm->cm_datamap,
					BUS_DMASYNC_POSTREAD);
		if (cm->cm_flags & AAC_CMD_DATAOUT)
			bus_dmamap_sync(sc->aac_buffer_dmat, cm->cm_datamap,
					BUS_DMASYNC_POSTWRITE);

		bus_dmamap_unload(sc->aac_buffer_dmat, cm->cm_datamap);
	}
	cm->cm_flags &= ~AAC_CMD_MAPPED;
}