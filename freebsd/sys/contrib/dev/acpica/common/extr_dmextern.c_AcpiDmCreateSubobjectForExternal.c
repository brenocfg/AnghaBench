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
typedef  int UINT8 ;
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_10__ {TYPE_3__* Object; } ;
struct TYPE_8__ {TYPE_4__* Node; } ;
struct TYPE_7__ {int ParamCount; } ;
struct TYPE_9__ {TYPE_2__ Region; TYPE_1__ Method; } ;
typedef  TYPE_3__ ACPI_OPERAND_OBJECT ;
typedef  TYPE_4__ ACPI_NAMESPACE_NODE ;

/* Variables and functions */
#define  ACPI_TYPE_METHOD 129 
#define  ACPI_TYPE_REGION 128 
 TYPE_3__* AcpiUtCreateInternalObject (int const) ; 

void
AcpiDmCreateSubobjectForExternal (
    UINT8                   Type,
    ACPI_NAMESPACE_NODE     **Node,
    UINT32                  ParamCount)
{
    ACPI_OPERAND_OBJECT     *ObjDesc;


    switch (Type)
    {
    case ACPI_TYPE_METHOD:

        /* For methods, we need to save the argument count */

        ObjDesc = AcpiUtCreateInternalObject (ACPI_TYPE_METHOD);
        ObjDesc->Method.ParamCount = (UINT8) ParamCount;
        (*Node)->Object = ObjDesc;
        break;

    case ACPI_TYPE_REGION:

        /* Regions require a region sub-object */

        ObjDesc = AcpiUtCreateInternalObject (ACPI_TYPE_REGION);
        ObjDesc->Region.Node = *Node;
        (*Node)->Object = ObjDesc;
        break;

    default:

        break;
    }
}