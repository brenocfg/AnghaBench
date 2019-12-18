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
struct pvscsi_softc {int /*<<< orphan*/ * mm_res; int /*<<< orphan*/  mm_rid; int /*<<< orphan*/  dev; int /*<<< orphan*/ * parent_dmat; int /*<<< orphan*/ * buffer_dmat; scalar_t__ hcbs; int /*<<< orphan*/  hcb_cnt; scalar_t__ sim; scalar_t__ bus_path; } ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ CAM_REQ_CMP ; 
 int /*<<< orphan*/  M_PVSCSI ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cam_sim_free (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_sim_path (scalar_t__) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  free (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvscsi_dma_free_per_hcb (struct pvscsi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvscsi_free_interrupts (struct pvscsi_softc*) ; 
 int /*<<< orphan*/  pvscsi_free_rings (struct pvscsi_softc*) ; 
 scalar_t__ xpt_bus_deregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_free_path (scalar_t__) ; 

__attribute__((used)) static void
pvscsi_free_all(struct pvscsi_softc *sc)
{

	if (sc->sim) {
		int32_t status;

		if (sc->bus_path) {
			xpt_free_path(sc->bus_path);
		}

		status = xpt_bus_deregister(cam_sim_path(sc->sim));
		if (status != CAM_REQ_CMP) {
			device_printf(sc->dev,
			    "Error deregistering bus, status=%d\n", status);
		}

		cam_sim_free(sc->sim, TRUE);
	}

	pvscsi_dma_free_per_hcb(sc, sc->hcb_cnt);

	if (sc->hcbs) {
		free(sc->hcbs, M_PVSCSI);
	}

	pvscsi_free_rings(sc);

	pvscsi_free_interrupts(sc);

	if (sc->buffer_dmat != NULL) {
		bus_dma_tag_destroy(sc->buffer_dmat);
	}

	if (sc->parent_dmat != NULL) {
		bus_dma_tag_destroy(sc->parent_dmat);
	}

	if (sc->mm_res != NULL) {
		bus_release_resource(sc->dev, SYS_RES_MEMORY, sc->mm_rid,
		    sc->mm_res);
	}
}