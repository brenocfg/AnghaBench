#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_4__ {int Valid; scalar_t__ Address; } ;
typedef  void* ACPI_HANDLE ;
typedef  TYPE_1__ ACPI_DEVICE_INFO ;

/* Variables and functions */
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int ACPI_VALID_ADR ; 
 int /*<<< orphan*/  AE_CTRL_TERMINATE ; 
 int /*<<< orphan*/  AcpiGetObjectInfo (void*,TYPE_1__**) ; 
 int /*<<< orphan*/  AcpiOsFree (TYPE_1__*) ; 

__attribute__((used)) static UINT32
acpi_uhub_find_rh_cb(ACPI_HANDLE ah, UINT32 nl, void *ctx, void **status)
{
	ACPI_DEVICE_INFO *devinfo;
	UINT32 ret;

	*status = NULL;
	devinfo = NULL;

	ret = AcpiGetObjectInfo(ah, &devinfo);
	if (ACPI_SUCCESS(ret)) {
		if ((devinfo->Valid & ACPI_VALID_ADR) &&
		    (devinfo->Address == 0)) {
			ret = AE_CTRL_TERMINATE;
			*status = ah;
		}
		AcpiOsFree(devinfo);
	}
	return (ret);
}