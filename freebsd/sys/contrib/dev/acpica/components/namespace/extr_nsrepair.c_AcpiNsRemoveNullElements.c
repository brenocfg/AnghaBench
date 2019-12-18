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
typedef  int UINT8 ;
typedef  scalar_t__ UINT32 ;
struct TYPE_8__ {int /*<<< orphan*/  FullPathname; } ;
struct TYPE_6__ {scalar_t__ Count; TYPE_2__** Elements; } ;
struct TYPE_7__ {TYPE_1__ Package; } ;
typedef  TYPE_2__ ACPI_OPERAND_OBJECT ;
typedef  TYPE_3__ ACPI_EVALUATE_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_REPAIR ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_NAME (int /*<<< orphan*/ ) ; 
#define  ACPI_PTYPE1_FIXED 138 
#define  ACPI_PTYPE1_OPTION 137 
#define  ACPI_PTYPE1_VAR 136 
#define  ACPI_PTYPE2 135 
#define  ACPI_PTYPE2_COUNT 134 
#define  ACPI_PTYPE2_FIXED 133 
#define  ACPI_PTYPE2_FIX_VAR 132 
#define  ACPI_PTYPE2_MIN 131 
#define  ACPI_PTYPE2_PKG_COUNT 130 
#define  ACPI_PTYPE2_REV_FIXED 129 
#define  ACPI_PTYPE2_VAR_VAR 128 
 int /*<<< orphan*/  NsRemoveNullElements ; 

void
AcpiNsRemoveNullElements (
    ACPI_EVALUATE_INFO      *Info,
    UINT8                   PackageType,
    ACPI_OPERAND_OBJECT     *ObjDesc)
{
    ACPI_OPERAND_OBJECT     **Source;
    ACPI_OPERAND_OBJECT     **Dest;
    UINT32                  Count;
    UINT32                  NewCount;
    UINT32                  i;


    ACPI_FUNCTION_NAME (NsRemoveNullElements);


    /*
     * We can safely remove all NULL elements from these package types:
     * PTYPE1_VAR packages contain a variable number of simple data types.
     * PTYPE2 packages contain a variable number of subpackages.
     */
    switch (PackageType)
    {
    case ACPI_PTYPE1_VAR:
    case ACPI_PTYPE2:
    case ACPI_PTYPE2_COUNT:
    case ACPI_PTYPE2_PKG_COUNT:
    case ACPI_PTYPE2_FIXED:
    case ACPI_PTYPE2_MIN:
    case ACPI_PTYPE2_REV_FIXED:
    case ACPI_PTYPE2_FIX_VAR:
        break;

    default:
    case ACPI_PTYPE2_VAR_VAR:
    case ACPI_PTYPE1_FIXED:
    case ACPI_PTYPE1_OPTION:
        return;
    }

    Count = ObjDesc->Package.Count;
    NewCount = Count;

    Source = ObjDesc->Package.Elements;
    Dest = Source;

    /* Examine all elements of the package object, remove nulls */

    for (i = 0; i < Count; i++)
    {
        if (!*Source)
        {
            NewCount--;
        }
        else
        {
            *Dest = *Source;
            Dest++;
        }

        Source++;
    }

    /* Update parent package if any null elements were removed */

    if (NewCount < Count)
    {
        ACPI_DEBUG_PRINT ((ACPI_DB_REPAIR,
            "%s: Found and removed %u NULL elements\n",
            Info->FullPathname, (Count - NewCount)));

        /* NULL terminate list and update the package count */

        *Dest = NULL;
        ObjDesc->Package.Count = NewCount;
    }
}