#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  scalar_t__ uint32_t ;
struct mpr_softc {TYPE_1__* fw_diag_buffer_list; } ;
struct TYPE_4__ {size_t buffer_type; scalar_t__ unique_id; scalar_t__ owned_by_firmware; scalar_t__ valid_data; scalar_t__ immediate; int /*<<< orphan*/  size; int /*<<< orphan*/ * product_specific; int /*<<< orphan*/  extended_type; } ;
typedef  TYPE_1__ mpr_fw_diagnostic_buffer_t ;
struct TYPE_5__ {scalar_t__ UniqueId; size_t BufferType; int /*<<< orphan*/  ApplicationFlags; scalar_t__ DiagnosticFlags; scalar_t__ DriverAddedBufferSize; int /*<<< orphan*/  TotalBufferSize; int /*<<< orphan*/ * ProductSpecific; int /*<<< orphan*/  ExtendedType; } ;
typedef  TYPE_2__ mpr_fw_diag_query_t ;

/* Variables and functions */
 size_t MPI2_DIAG_BUF_TYPE_COUNT ; 
 size_t MPI2_DIAG_BUF_TYPE_TRACE ; 
 int MPR_DIAG_FAILURE ; 
 int MPR_DIAG_SUCCESS ; 
 size_t MPR_FW_DIAGNOSTIC_UID_NOT_FOUND ; 
 scalar_t__ MPR_FW_DIAG_ERROR_INVALID_UID ; 
 int /*<<< orphan*/  MPR_FW_DIAG_FLAG_APP_OWNED ; 
 int /*<<< orphan*/  MPR_FW_DIAG_FLAG_BUFFER_VALID ; 
 int /*<<< orphan*/  MPR_FW_DIAG_FLAG_FW_BUFFER_ACCESS ; 
 scalar_t__ MPR_FW_DIAG_INVALID_UID ; 
 size_t mpr_get_fw_diag_buffer_number (struct mpr_softc*,scalar_t__) ; 

__attribute__((used)) static int
mpr_diag_query(struct mpr_softc *sc, mpr_fw_diag_query_t *diag_query,
    uint32_t *return_code)
{
	mpr_fw_diagnostic_buffer_t	*pBuffer;
	uint8_t				i;
	uint32_t			unique_id;

	unique_id = diag_query->UniqueId;

	/*
	 * If ID is valid, query on ID.
	 * If ID is invalid, query on buffer type.
	 */
	if (unique_id == MPR_FW_DIAG_INVALID_UID) {
		i = diag_query->BufferType;
		if (i >= MPI2_DIAG_BUF_TYPE_COUNT) {
			*return_code = MPR_FW_DIAG_ERROR_INVALID_UID;
			return (MPR_DIAG_FAILURE);
		}
	} else {
		i = mpr_get_fw_diag_buffer_number(sc, unique_id);
		if (i == MPR_FW_DIAGNOSTIC_UID_NOT_FOUND) {
			*return_code = MPR_FW_DIAG_ERROR_INVALID_UID;
			return (MPR_DIAG_FAILURE);
		}
	}

	/*
	 * Fill query structure with the diag buffer info.
	 */
	pBuffer = &sc->fw_diag_buffer_list[i];
	diag_query->BufferType = pBuffer->buffer_type;
	diag_query->ExtendedType = pBuffer->extended_type;
	if (diag_query->BufferType == MPI2_DIAG_BUF_TYPE_TRACE) {
		for (i = 0; i < (sizeof(diag_query->ProductSpecific) / 4);
		    i++) {
			diag_query->ProductSpecific[i] =
			    pBuffer->product_specific[i];
		}
	}
	diag_query->TotalBufferSize = pBuffer->size;
	diag_query->DriverAddedBufferSize = 0;
	diag_query->UniqueId = pBuffer->unique_id;
	diag_query->ApplicationFlags = 0;
	diag_query->DiagnosticFlags = 0;

	/*
	 * Set/Clear application flags
	 */
	if (pBuffer->immediate) {
		diag_query->ApplicationFlags &= ~MPR_FW_DIAG_FLAG_APP_OWNED;
	} else {
		diag_query->ApplicationFlags |= MPR_FW_DIAG_FLAG_APP_OWNED;
	}
	if (pBuffer->valid_data || pBuffer->owned_by_firmware) {
		diag_query->ApplicationFlags |= MPR_FW_DIAG_FLAG_BUFFER_VALID;
	} else {
		diag_query->ApplicationFlags &= ~MPR_FW_DIAG_FLAG_BUFFER_VALID;
	}
	if (pBuffer->owned_by_firmware) {
		diag_query->ApplicationFlags |=
		    MPR_FW_DIAG_FLAG_FW_BUFFER_ACCESS;
	} else {
		diag_query->ApplicationFlags &=
		    ~MPR_FW_DIAG_FLAG_FW_BUFFER_ACCESS;
	}

	return (MPR_DIAG_SUCCESS);
}