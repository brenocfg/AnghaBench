#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_2__ {int DisplayType; int /*<<< orphan*/  AddressSpaceId; int /*<<< orphan*/  DebugLevel; int /*<<< orphan*/  OwnerId; scalar_t__ Count; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_1__ ACPI_REGION_WALK_INFO ;

/* Variables and functions */
 int ACPI_DISPLAY_SHORT ; 
 int ACPI_DISPLAY_SUMMARY ; 
 int /*<<< orphan*/  ACPI_OWNER_ID_MAX ; 
 int /*<<< orphan*/  ACPI_ROOT_OBJECT ; 
 int /*<<< orphan*/  ACPI_TYPE_LOCAL_REGION_FIELD ; 
 int /*<<< orphan*/  ACPI_UINT32_MAX ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiDbWalkForFields ; 
 int /*<<< orphan*/  AcpiWalkNamespace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *) ; 

ACPI_STATUS
AcpiDbDisplayFields (
    UINT32                  AddressSpaceId)
{
    ACPI_REGION_WALK_INFO  Info;


    Info.Count = 0;
    Info.OwnerId = ACPI_OWNER_ID_MAX;
    Info.DebugLevel = ACPI_UINT32_MAX;
    Info.DisplayType = ACPI_DISPLAY_SUMMARY | ACPI_DISPLAY_SHORT;
    Info.AddressSpaceId = AddressSpaceId;

    /* Walk the namespace from the root */

    (void) AcpiWalkNamespace (ACPI_TYPE_LOCAL_REGION_FIELD, ACPI_ROOT_OBJECT,
          ACPI_UINT32_MAX, AcpiDbWalkForFields, NULL,
          (void *) &Info, NULL);

    return (AE_OK);
}