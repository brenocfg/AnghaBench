#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT32 ;
struct TYPE_17__ {TYPE_8__* Handler; TYPE_8__** NotifyList; } ;
struct TYPE_16__ {TYPE_8__* Handler; TYPE_8__** NotifyList; } ;
struct TYPE_15__ {TYPE_8__** NotifyList; } ;
struct TYPE_14__ {TYPE_8__* Handler; } ;
struct TYPE_13__ {TYPE_8__* Handler; TYPE_8__** NotifyList; } ;
struct TYPE_12__ {size_t Count; TYPE_8__** Elements; } ;
struct TYPE_11__ {size_t Type; } ;
struct TYPE_18__ {TYPE_7__ ThermalZone; TYPE_6__ Processor; TYPE_5__ PowerResource; TYPE_4__ Region; TYPE_3__ Device; TYPE_2__ Package; TYPE_1__ Common; } ;
typedef  TYPE_8__ ACPI_OPERAND_OBJECT ;

/* Variables and functions */
#define  ACPI_TYPE_BUFFER_FIELD 134 
#define  ACPI_TYPE_DEVICE 133 
 size_t ACPI_TYPE_LOCAL_REGION_FIELD ; 
 size_t ACPI_TYPE_NS_NODE_MAX ; 
#define  ACPI_TYPE_PACKAGE 132 
#define  ACPI_TYPE_POWER 131 
#define  ACPI_TYPE_PROCESSOR 130 
#define  ACPI_TYPE_REGION 129 
#define  ACPI_TYPE_THERMAL 128 
 int /*<<< orphan*/  AcpiGbl_NumObjects ; 
 int /*<<< orphan*/ * AcpiGbl_ObjTypeCount ; 
 int /*<<< orphan*/  AcpiGbl_ObjTypeCountMisc ; 
 int /*<<< orphan*/  AcpiNsGetSecondaryObject (TYPE_8__*) ; 

__attribute__((used)) static void
AcpiDbEnumerateObject (
    ACPI_OPERAND_OBJECT     *ObjDesc)
{
    UINT32                  i;


    if (!ObjDesc)
    {
        return;
    }

    /* Enumerate this object first */

    AcpiGbl_NumObjects++;

    if (ObjDesc->Common.Type > ACPI_TYPE_NS_NODE_MAX)
    {
        AcpiGbl_ObjTypeCountMisc++;
    }
    else
    {
        AcpiGbl_ObjTypeCount [ObjDesc->Common.Type]++;
    }

    /* Count the sub-objects */

    switch (ObjDesc->Common.Type)
    {
    case ACPI_TYPE_PACKAGE:

        for (i = 0; i < ObjDesc->Package.Count; i++)
        {
            AcpiDbEnumerateObject (ObjDesc->Package.Elements[i]);
        }
        break;

    case ACPI_TYPE_DEVICE:

        AcpiDbEnumerateObject (ObjDesc->Device.NotifyList[0]);
        AcpiDbEnumerateObject (ObjDesc->Device.NotifyList[1]);
        AcpiDbEnumerateObject (ObjDesc->Device.Handler);
        break;

    case ACPI_TYPE_BUFFER_FIELD:

        if (AcpiNsGetSecondaryObject (ObjDesc))
        {
            AcpiGbl_ObjTypeCount [ACPI_TYPE_BUFFER_FIELD]++;
        }
        break;

    case ACPI_TYPE_REGION:

        AcpiGbl_ObjTypeCount [ACPI_TYPE_LOCAL_REGION_FIELD ]++;
        AcpiDbEnumerateObject (ObjDesc->Region.Handler);
        break;

    case ACPI_TYPE_POWER:

        AcpiDbEnumerateObject (ObjDesc->PowerResource.NotifyList[0]);
        AcpiDbEnumerateObject (ObjDesc->PowerResource.NotifyList[1]);
        break;

    case ACPI_TYPE_PROCESSOR:

        AcpiDbEnumerateObject (ObjDesc->Processor.NotifyList[0]);
        AcpiDbEnumerateObject (ObjDesc->Processor.NotifyList[1]);
        AcpiDbEnumerateObject (ObjDesc->Processor.Handler);
        break;

    case ACPI_TYPE_THERMAL:

        AcpiDbEnumerateObject (ObjDesc->ThermalZone.NotifyList[0]);
        AcpiDbEnumerateObject (ObjDesc->ThermalZone.NotifyList[1]);
        AcpiDbEnumerateObject (ObjDesc->ThermalZone.Handler);
        break;

    default:

        break;
    }
}