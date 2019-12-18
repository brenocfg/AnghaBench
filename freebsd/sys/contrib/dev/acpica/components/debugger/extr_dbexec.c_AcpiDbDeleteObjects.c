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
typedef  size_t UINT32 ;
struct TYPE_7__ {size_t Count; TYPE_3__* Elements; } ;
struct TYPE_6__ {TYPE_3__* Pointer; } ;
struct TYPE_8__ {int Type; TYPE_2__ Package; TYPE_1__ Buffer; } ;
typedef  TYPE_3__ ACPI_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FREE (TYPE_3__*) ; 
#define  ACPI_TYPE_BUFFER 129 
#define  ACPI_TYPE_PACKAGE 128 

void
AcpiDbDeleteObjects (
    UINT32                  Count,
    ACPI_OBJECT             *Objects)
{
    UINT32                  i;


    for (i = 0; i < Count; i++)
    {
        switch (Objects[i].Type)
        {
        case ACPI_TYPE_BUFFER:

            ACPI_FREE (Objects[i].Buffer.Pointer);
            break;

        case ACPI_TYPE_PACKAGE:

            /* Recursive call to delete package elements */

            AcpiDbDeleteObjects (Objects[i].Package.Count,
                Objects[i].Package.Elements);

            /* Free the elements array */

            ACPI_FREE (Objects[i].Package.Elements);
            break;

        default:

            break;
        }
    }
}