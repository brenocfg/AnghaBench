#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ uint16_t ;
struct nvdimm_dev {scalar_t__ label_area_size; int /*<<< orphan*/  max_label_xfer; int /*<<< orphan*/  nv_dev; } ;
typedef  int /*<<< orphan*/  params ;
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  UINT8 ;
struct TYPE_10__ {int Length; int /*<<< orphan*/ * Pointer; } ;
struct TYPE_8__ {int Length; int /*<<< orphan*/ * Pointer; } ;
struct TYPE_7__ {int Count; TYPE_3__* Elements; } ;
struct TYPE_9__ {scalar_t__ Type; TYPE_2__ Buffer; TYPE_1__ Package; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_3__ ACPI_OBJECT ;
typedef  int /*<<< orphan*/ * ACPI_HANDLE ;
typedef  TYPE_4__ ACPI_BUFFER ;

/* Variables and functions */
 int ACPI_ALLOCATE_BUFFER ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_TYPE_BUFFER ; 
 scalar_t__ ACPI_TYPE_PACKAGE ; 
 int /*<<< orphan*/  AcpiOsFree (int /*<<< orphan*/ *) ; 
 int ENODEV ; 
 int ENXIO ; 
 int /*<<< orphan*/  INTEL_NVDIMM_DSM_GET_LABEL_DATA ; 
 int /*<<< orphan*/  INTEL_NVDIMM_DSM_REV ; 
 scalar_t__ MIN (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_EvaluateDSM (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  intel_nvdimm_dsm_uuid ; 
 int /*<<< orphan*/ * nvdimm_root_get_acpi_handle (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
read_label_area(struct nvdimm_dev *nv, uint8_t *dest, off_t offset,
    off_t length)
{
	ACPI_BUFFER result;
	ACPI_HANDLE handle;
	ACPI_OBJECT params_pkg, params_buf, *result_buf;
	ACPI_STATUS status;
	uint32_t params[2];
	off_t to_read;
	int error;

	error = 0;
	handle = nvdimm_root_get_acpi_handle(nv->nv_dev);
	if (offset < 0 || length <= 0 ||
	    offset + length > nv->label_area_size ||
	    handle == NULL)
		return (ENODEV);
	params_pkg.Type = ACPI_TYPE_PACKAGE;
	params_pkg.Package.Count = 1;
	params_pkg.Package.Elements = &params_buf;
	params_buf.Type = ACPI_TYPE_BUFFER;
	params_buf.Buffer.Length = sizeof(params);
	params_buf.Buffer.Pointer = (UINT8 *)params;
	while (length > 0) {
		to_read = MIN(length, nv->max_label_xfer);
		params[0] = offset;
		params[1] = to_read;
		result.Length = ACPI_ALLOCATE_BUFFER;
		result.Pointer = NULL;
		status = acpi_EvaluateDSM(handle,
		    (uint8_t *)&intel_nvdimm_dsm_uuid, INTEL_NVDIMM_DSM_REV,
		    INTEL_NVDIMM_DSM_GET_LABEL_DATA, &params_pkg, &result);
		if (ACPI_FAILURE(status) ||
		    result.Length < sizeof(ACPI_OBJECT) ||
		    result.Pointer == NULL) {
			error = ENXIO;
			break;
		}
		result_buf = (ACPI_OBJECT *)result.Pointer;
		if (result_buf->Type != ACPI_TYPE_BUFFER ||
		    result_buf->Buffer.Pointer == NULL ||
		    result_buf->Buffer.Length != 4 + to_read ||
		    ((uint16_t *)result_buf->Buffer.Pointer)[0] != 0) {
			error = ENXIO;
			break;
		}
		bcopy(result_buf->Buffer.Pointer + 4, dest, to_read);
		dest += to_read;
		offset += to_read;
		length -= to_read;
		if (result.Pointer != NULL) {
			AcpiOsFree(result.Pointer);
			result.Pointer = NULL;
		}
	}
	if (result.Pointer != NULL)
		AcpiOsFree(result.Pointer);
	return (error);
}