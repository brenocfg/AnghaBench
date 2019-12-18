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
struct mps_softc {int /*<<< orphan*/  buffer_dmat; } ;
struct mps_command {int cm_flags; scalar_t__ cm_length; int /*<<< orphan*/ * cm_sge; int /*<<< orphan*/ * cm_data; int /*<<< orphan*/  cm_dmamap; int /*<<< orphan*/  cm_uio; } ;

/* Variables and functions */
 int MPS_CM_FLAGS_USE_CCB ; 
 int MPS_CM_FLAGS_USE_UIO ; 
 int bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,struct mps_command*,int /*<<< orphan*/ ) ; 
 int bus_dmamap_load_ccb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct mps_command*,int /*<<< orphan*/ ) ; 
 int bus_dmamap_load_uio (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct mps_command*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mps_add_dmaseg (struct mps_command*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mps_data_cb ; 
 int /*<<< orphan*/  mps_data_cb2 ; 
 int /*<<< orphan*/  mps_enqueue_request (struct mps_softc*,struct mps_command*) ; 

int
mps_map_command(struct mps_softc *sc, struct mps_command *cm)
{
	int error = 0;

	if (cm->cm_flags & MPS_CM_FLAGS_USE_UIO) {
		error = bus_dmamap_load_uio(sc->buffer_dmat, cm->cm_dmamap,
		    &cm->cm_uio, mps_data_cb2, cm, 0);
	} else if (cm->cm_flags & MPS_CM_FLAGS_USE_CCB) {
		error = bus_dmamap_load_ccb(sc->buffer_dmat, cm->cm_dmamap,
		    cm->cm_data, mps_data_cb, cm, 0);
	} else if ((cm->cm_data != NULL) && (cm->cm_length != 0)) {
		error = bus_dmamap_load(sc->buffer_dmat, cm->cm_dmamap,
		    cm->cm_data, cm->cm_length, mps_data_cb, cm, 0);
	} else {
		/* Add a zero-length element as needed */
		if (cm->cm_sge != NULL)
			mps_add_dmaseg(cm, 0, 0, 0, 1);
		mps_enqueue_request(sc, cm);	
	}

	return (error);
}