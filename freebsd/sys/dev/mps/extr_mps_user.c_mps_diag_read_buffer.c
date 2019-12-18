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
struct mps_softc {scalar_t__ fw_diag_buffer; int /*<<< orphan*/  fw_diag_map; int /*<<< orphan*/  fw_diag_dmat; TYPE_1__* fw_diag_buffer_list; } ;
struct TYPE_5__ {scalar_t__ size; int /*<<< orphan*/  owned_by_firmware; scalar_t__ force_release; } ;
typedef  TYPE_1__ mps_fw_diagnostic_buffer_t ;
struct TYPE_6__ {scalar_t__ StartingOffset; scalar_t__ BytesToRead; int Flags; scalar_t__ Status; int /*<<< orphan*/  UniqueId; } ;
typedef  TYPE_2__ mps_diag_read_buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int MPS_DIAG_FAILURE ; 
 int MPS_DIAG_SUCCESS ; 
 size_t MPS_FW_DIAGNOSTIC_UID_NOT_FOUND ; 
 int /*<<< orphan*/  MPS_FW_DIAG_ERROR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  MPS_FW_DIAG_ERROR_INVALID_UID ; 
 int MPS_FW_DIAG_FLAG_FORCE_RELEASE ; 
 int MPS_FW_DIAG_FLAG_REREGISTER ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ copyout (size_t*,size_t*,scalar_t__) ; 
 size_t mps_get_fw_diag_buffer_number (struct mps_softc*,int /*<<< orphan*/ ) ; 
 int mps_post_fw_diag_buffer (struct mps_softc*,TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mps_diag_read_buffer(struct mps_softc *sc,
    mps_diag_read_buffer_t *diag_read_buffer, uint8_t *ioctl_buf,
    uint32_t *return_code)
{
	mps_fw_diagnostic_buffer_t	*pBuffer;
	uint8_t				i, *pData;
	uint32_t			unique_id;
	int				status;

	unique_id = diag_read_buffer->UniqueId;

	/*
	 * Get the current buffer and look up the unique ID.  The unique ID
	 * should be there.
	 */
	i = mps_get_fw_diag_buffer_number(sc, unique_id);
	if (i == MPS_FW_DIAGNOSTIC_UID_NOT_FOUND) {
		*return_code = MPS_FW_DIAG_ERROR_INVALID_UID;
		return (MPS_DIAG_FAILURE);
	}

	pBuffer = &sc->fw_diag_buffer_list[i];

	/*
	 * Make sure requested read is within limits
	 */
	if (diag_read_buffer->StartingOffset + diag_read_buffer->BytesToRead >
	    pBuffer->size) {
		*return_code = MPS_FW_DIAG_ERROR_INVALID_PARAMETER;
		return (MPS_DIAG_FAILURE);
	}

	/* Sync the DMA map before we copy to userland. */
	bus_dmamap_sync(sc->fw_diag_dmat, sc->fw_diag_map,
	    BUS_DMASYNC_POSTREAD);

	/*
	 * Copy the requested data from DMA to the diag_read_buffer.  The DMA
	 * buffer that was allocated is one contiguous buffer.
	 */
	pData = (uint8_t *)(sc->fw_diag_buffer +
	    diag_read_buffer->StartingOffset);
	if (copyout(pData, ioctl_buf, diag_read_buffer->BytesToRead) != 0)
		return (MPS_DIAG_FAILURE);
	diag_read_buffer->Status = 0;

	/*
	 * Set or clear the Force Release flag.
	 */
	if (pBuffer->force_release) {
		diag_read_buffer->Flags |= MPS_FW_DIAG_FLAG_FORCE_RELEASE;
	} else {
		diag_read_buffer->Flags &= ~MPS_FW_DIAG_FLAG_FORCE_RELEASE;
	}

	/*
	 * If buffer is to be reregistered, make sure it's not already owned by
	 * firmware first.
	 */
	status = MPS_DIAG_SUCCESS;
	if (!pBuffer->owned_by_firmware) {
		if (diag_read_buffer->Flags & MPS_FW_DIAG_FLAG_REREGISTER) {
			status = mps_post_fw_diag_buffer(sc, pBuffer,
			    return_code);
		}
	}

	return (status);
}