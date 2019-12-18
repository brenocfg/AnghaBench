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
struct mps_softc {TYPE_1__* fw_diag_buffer_list; } ;
struct TYPE_5__ {int /*<<< orphan*/  owned_by_firmware; } ;
typedef  TYPE_1__ mps_fw_diagnostic_buffer_t ;
struct TYPE_6__ {int /*<<< orphan*/  UniqueId; } ;
typedef  TYPE_2__ mps_fw_diag_release_t ;

/* Variables and functions */
 int MPS_DIAG_FAILURE ; 
 size_t MPS_FW_DIAGNOSTIC_UID_NOT_FOUND ; 
 int /*<<< orphan*/  MPS_FW_DIAG_ERROR_ALREADY_RELEASED ; 
 int /*<<< orphan*/  MPS_FW_DIAG_ERROR_INVALID_UID ; 
 int /*<<< orphan*/  MPS_FW_DIAG_TYPE_RELEASE ; 
 size_t mps_get_fw_diag_buffer_number (struct mps_softc*,int /*<<< orphan*/ ) ; 
 int mps_release_fw_diag_buffer (struct mps_softc*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mps_diag_release(struct mps_softc *sc, mps_fw_diag_release_t *diag_release,
    uint32_t *return_code)
{
	mps_fw_diagnostic_buffer_t	*pBuffer;
	uint8_t				i;
	uint32_t			unique_id;
	int				status;

	unique_id = diag_release->UniqueId;

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
	 * If buffer is not owned by firmware, it's already been released.
	 */
	if (!pBuffer->owned_by_firmware) {
		*return_code = MPS_FW_DIAG_ERROR_ALREADY_RELEASED;
		return (MPS_DIAG_FAILURE);
	}

	/*
	 * Release the buffer.
	 */
	status = mps_release_fw_diag_buffer(sc, pBuffer, return_code,
	    MPS_FW_DIAG_TYPE_RELEASE);
	return (status);
}