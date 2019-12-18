#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct mpr_softc {scalar_t__ fw_diag_busaddr; int /*<<< orphan*/ * fw_diag_dmat; int /*<<< orphan*/ * fw_diag_buffer; int /*<<< orphan*/  fw_diag_map; TYPE_1__* fw_diag_buffer_list; } ;
struct TYPE_5__ {int /*<<< orphan*/  unique_id; int /*<<< orphan*/  owned_by_firmware; } ;
typedef  TYPE_1__ mpr_fw_diagnostic_buffer_t ;
struct TYPE_6__ {int /*<<< orphan*/  UniqueId; } ;
typedef  TYPE_2__ mpr_fw_diag_unregister_t ;

/* Variables and functions */
 int MPR_DIAG_FAILURE ; 
 int MPR_DIAG_SUCCESS ; 
 size_t MPR_FW_DIAGNOSTIC_UID_NOT_FOUND ; 
 int /*<<< orphan*/  MPR_FW_DIAG_ERROR_INVALID_UID ; 
 int /*<<< orphan*/  MPR_FW_DIAG_INVALID_UID ; 
 int /*<<< orphan*/  MPR_FW_DIAG_TYPE_UNREGISTER ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t mpr_get_fw_diag_buffer_number (struct mpr_softc*,int /*<<< orphan*/ ) ; 
 int mpr_release_fw_diag_buffer (struct mpr_softc*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mpr_diag_unregister(struct mpr_softc *sc,
    mpr_fw_diag_unregister_t *diag_unregister, uint32_t *return_code)
{
	mpr_fw_diagnostic_buffer_t	*pBuffer;
	uint8_t				i;
	uint32_t			unique_id;
	int				status;

	unique_id = diag_unregister->UniqueId;

	/*
	 * Get the current buffer and look up the unique ID.  The unique ID
	 * should be there.
	 */
	i = mpr_get_fw_diag_buffer_number(sc, unique_id);
	if (i == MPR_FW_DIAGNOSTIC_UID_NOT_FOUND) {
		*return_code = MPR_FW_DIAG_ERROR_INVALID_UID;
		return (MPR_DIAG_FAILURE);
	}

	pBuffer = &sc->fw_diag_buffer_list[i];

	/*
	 * Try to release the buffer from FW before freeing it.  If release
	 * fails, don't free the DMA buffer in case FW tries to access it
	 * later.  If buffer is not owned by firmware, can't release it.
	 */
	if (!pBuffer->owned_by_firmware) {
		status = MPR_DIAG_SUCCESS;
	} else {
		status = mpr_release_fw_diag_buffer(sc, pBuffer, return_code,
		    MPR_FW_DIAG_TYPE_UNREGISTER);
	}

	/*
	 * At this point, return the current status no matter what happens with
	 * the DMA buffer.
	 */
	pBuffer->unique_id = MPR_FW_DIAG_INVALID_UID;
	if (status == MPR_DIAG_SUCCESS) {
		if (sc->fw_diag_busaddr != 0) {
			bus_dmamap_unload(sc->fw_diag_dmat, sc->fw_diag_map);
			sc->fw_diag_busaddr = 0;
		}
		if (sc->fw_diag_buffer != NULL) {
			bus_dmamem_free(sc->fw_diag_dmat, sc->fw_diag_buffer,
			    sc->fw_diag_map);
			sc->fw_diag_buffer = NULL;
		}
		if (sc->fw_diag_dmat != NULL) {
			bus_dma_tag_destroy(sc->fw_diag_dmat);
			sc->fw_diag_dmat = NULL;
		}
	}

	return (status);
}