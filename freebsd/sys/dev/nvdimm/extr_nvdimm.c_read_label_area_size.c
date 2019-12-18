#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  void* uint32_t ;
struct nvdimm_dev {void* max_label_xfer; void* label_area_size; int /*<<< orphan*/  nv_dev; } ;
struct TYPE_8__ {int Length; TYPE_2__* Pointer; } ;
struct TYPE_6__ {int Length; scalar_t__ Pointer; } ;
struct TYPE_7__ {scalar_t__ Type; TYPE_1__ Buffer; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_2__ ACPI_OBJECT ;
typedef  int /*<<< orphan*/ * ACPI_HANDLE ;
typedef  TYPE_3__ ACPI_BUFFER ;

/* Variables and functions */
 int ACPI_ALLOCATE_BUFFER ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_TYPE_BUFFER ; 
 int /*<<< orphan*/  AcpiOsFree (TYPE_2__*) ; 
 int ENODEV ; 
 int ENXIO ; 
 int /*<<< orphan*/  INTEL_NVDIMM_DSM_GET_LABEL_SIZE ; 
 int /*<<< orphan*/  INTEL_NVDIMM_DSM_REV ; 
 int /*<<< orphan*/  acpi_EvaluateDSM (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  intel_nvdimm_dsm_uuid ; 
 int /*<<< orphan*/ * nvdimm_root_get_acpi_handle (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
read_label_area_size(struct nvdimm_dev *nv)
{
	ACPI_OBJECT *result_buffer;
	ACPI_HANDLE handle;
	ACPI_STATUS status;
	ACPI_BUFFER result;
	uint32_t *out;
	int error;

	handle = nvdimm_root_get_acpi_handle(nv->nv_dev);
	if (handle == NULL)
		return (ENODEV);
	result.Length = ACPI_ALLOCATE_BUFFER;
	result.Pointer = NULL;
	status = acpi_EvaluateDSM(handle, (uint8_t *)&intel_nvdimm_dsm_uuid,
	    INTEL_NVDIMM_DSM_REV, INTEL_NVDIMM_DSM_GET_LABEL_SIZE, NULL,
	    &result);
	error = ENXIO;
	if (ACPI_SUCCESS(status) && result.Pointer != NULL &&
	    result.Length >= sizeof(ACPI_OBJECT)) {
		result_buffer = result.Pointer;
		if (result_buffer->Type == ACPI_TYPE_BUFFER &&
		    result_buffer->Buffer.Length >= 12) {
			out = (uint32_t *)result_buffer->Buffer.Pointer;
			nv->label_area_size = out[1];
			nv->max_label_xfer = out[2];
			error = 0;
		}
	}
	if (result.Pointer != NULL)
		AcpiOsFree(result.Pointer);
	return (error);
}