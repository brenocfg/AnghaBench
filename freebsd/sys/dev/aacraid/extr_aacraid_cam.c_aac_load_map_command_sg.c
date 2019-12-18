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
struct aac_softc {int /*<<< orphan*/  flags; int /*<<< orphan*/  aac_buffer_dmat; } ;
struct aac_command {int /*<<< orphan*/  cm_datalen; int /*<<< orphan*/  cm_data; int /*<<< orphan*/  cm_datamap; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAC_QUEUE_FRZN ; 
 int EINPROGRESS ; 
 char* HBA_FLAGS_DBG_FUNCTION_ENTRY_B ; 
 char* HBA_FLAGS_DBG_INIT_B ; 
 int /*<<< orphan*/  aacraid_map_command_sg ; 
 int bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct aac_command*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwprintf (struct aac_softc*,char*,char*) ; 
 int /*<<< orphan*/  panic (char*,int) ; 

__attribute__((used)) static int
aac_load_map_command_sg(struct aac_softc *sc, struct aac_command *cm)
{
	int error;

	fwprintf(sc, HBA_FLAGS_DBG_FUNCTION_ENTRY_B, "");
	error = bus_dmamap_load(sc->aac_buffer_dmat,
				cm->cm_datamap, cm->cm_data, cm->cm_datalen,
				aacraid_map_command_sg, cm, 0);
	if (error == EINPROGRESS) {
		fwprintf(sc, HBA_FLAGS_DBG_INIT_B, "freezing queue\n");
		sc->flags |= AAC_QUEUE_FRZN;
		error = 0;
	} else if (error != 0) {
		panic("aac_load_map_command_sg: unexpected error %d from "
	     		"busdma", error);
	}
	return(error);
}