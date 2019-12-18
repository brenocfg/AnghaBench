#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_18__ {size_t Value; int /*<<< orphan*/  Class; TYPE_6__* Node; TYPE_6__* Object; TYPE_6__** Where; int /*<<< orphan*/  TargetType; } ;
struct TYPE_15__ {int /*<<< orphan*/  Type; } ;
struct TYPE_20__ {TYPE_4__ Reference; TYPE_1__ Common; } ;
struct TYPE_19__ {TYPE_3__* Arguments; TYPE_2__* LocalVariables; } ;
struct TYPE_17__ {TYPE_6__* Object; } ;
struct TYPE_16__ {TYPE_6__* Object; } ;
typedef  TYPE_5__ ACPI_WALK_STATE ;
typedef  TYPE_6__ ACPI_OPERAND_OBJECT ;
typedef  TYPE_6__ ACPI_NAMESPACE_NODE ;

/* Variables and functions */
#define  ACPI_DESC_TYPE_NAMED 140 
#define  ACPI_DESC_TYPE_OPERAND 139 
#define  ACPI_DESC_TYPE_PARSER 138 
 int ACPI_GET_DESCRIPTOR_TYPE (TYPE_6__*) ; 
#define  ACPI_REFCLASS_ARG 137 
#define  ACPI_REFCLASS_DEBUG 136 
#define  ACPI_REFCLASS_INDEX 135 
#define  ACPI_REFCLASS_LOCAL 134 
#define  ACPI_REFCLASS_NAME 133 
#define  ACPI_REFCLASS_REFOF 132 
#define  ACPI_REFCLASS_TABLE 131 
#define  ACPI_TYPE_BUFFER_FIELD 130 
 int /*<<< orphan*/  ACPI_TYPE_LOCAL_MAX ; 
#define  ACPI_TYPE_LOCAL_REFERENCE 129 
#define  ACPI_TYPE_PACKAGE 128 
 int /*<<< orphan*/  AcpiDbDecodeInternalObject (TYPE_6__*) ; 
 int /*<<< orphan*/  AcpiDbDecodeNode (TYPE_6__*) ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,...) ; 
 int /*<<< orphan*/  AcpiUtGetDescriptorName (TYPE_6__*) ; 
 int /*<<< orphan*/  AcpiUtGetReferenceName (TYPE_6__*) ; 

void
AcpiDbDisplayInternalObject (
    ACPI_OPERAND_OBJECT     *ObjDesc,
    ACPI_WALK_STATE         *WalkState)
{
    UINT8                   Type;


    AcpiOsPrintf ("%p ", ObjDesc);

    if (!ObjDesc)
    {
        AcpiOsPrintf ("<Null Object>\n");
        return;
    }

    /* Decode the object type */

    switch (ACPI_GET_DESCRIPTOR_TYPE (ObjDesc))
    {
    case ACPI_DESC_TYPE_PARSER:

        AcpiOsPrintf ("<Parser>  ");
        break;

    case ACPI_DESC_TYPE_NAMED:

        AcpiDbDecodeNode ((ACPI_NAMESPACE_NODE *) ObjDesc);
        break;

    case ACPI_DESC_TYPE_OPERAND:

        Type = ObjDesc->Common.Type;
        if (Type > ACPI_TYPE_LOCAL_MAX)
        {
            AcpiOsPrintf (" Type %X [Invalid Type]", (UINT32) Type);
            return;
        }

        /* Decode the ACPI object type */

        switch (ObjDesc->Common.Type)
        {
        case ACPI_TYPE_LOCAL_REFERENCE:

            AcpiOsPrintf ("[%s] ", AcpiUtGetReferenceName (ObjDesc));

            /* Decode the reference */

            switch (ObjDesc->Reference.Class)
            {
            case ACPI_REFCLASS_LOCAL:

                AcpiOsPrintf ("%X ", ObjDesc->Reference.Value);
                if (WalkState)
                {
                    ObjDesc = WalkState->LocalVariables
                        [ObjDesc->Reference.Value].Object;
                    AcpiOsPrintf ("%p", ObjDesc);
                    AcpiDbDecodeInternalObject (ObjDesc);
                }
                break;

            case ACPI_REFCLASS_ARG:

                AcpiOsPrintf ("%X ", ObjDesc->Reference.Value);
                if (WalkState)
                {
                    ObjDesc = WalkState->Arguments
                        [ObjDesc->Reference.Value].Object;
                    AcpiOsPrintf ("%p", ObjDesc);
                    AcpiDbDecodeInternalObject (ObjDesc);
                }
                break;

            case ACPI_REFCLASS_INDEX:

                switch (ObjDesc->Reference.TargetType)
                {
                case ACPI_TYPE_BUFFER_FIELD:

                    AcpiOsPrintf ("%p", ObjDesc->Reference.Object);
                    AcpiDbDecodeInternalObject (ObjDesc->Reference.Object);
                    break;

                case ACPI_TYPE_PACKAGE:

                    AcpiOsPrintf ("%p", ObjDesc->Reference.Where);
                    if (!ObjDesc->Reference.Where)
                    {
                        AcpiOsPrintf (" Uninitialized WHERE pointer");
                    }
                    else
                    {
                        AcpiDbDecodeInternalObject (
                            *(ObjDesc->Reference.Where));
                    }
                    break;

                default:

                    AcpiOsPrintf ("Unknown index target type");
                    break;
                }
                break;

            case ACPI_REFCLASS_REFOF:

                if (!ObjDesc->Reference.Object)
                {
                    AcpiOsPrintf (
                        "Uninitialized reference subobject pointer");
                    break;
                }

                /* Reference can be to a Node or an Operand object */

                switch (ACPI_GET_DESCRIPTOR_TYPE (ObjDesc->Reference.Object))
                {
                case ACPI_DESC_TYPE_NAMED:

                    AcpiDbDecodeNode (ObjDesc->Reference.Object);
                    break;

                case ACPI_DESC_TYPE_OPERAND:

                    AcpiDbDecodeInternalObject (ObjDesc->Reference.Object);
                    break;

                default:
                    break;
                }
                break;

            case ACPI_REFCLASS_NAME:

                AcpiDbDecodeNode (ObjDesc->Reference.Node);
                break;

            case ACPI_REFCLASS_DEBUG:
            case ACPI_REFCLASS_TABLE:

                AcpiOsPrintf ("\n");
                break;

            default:    /* Unknown reference class */

                AcpiOsPrintf ("%2.2X\n", ObjDesc->Reference.Class);
                break;
            }
            break;

        default:

            AcpiOsPrintf ("<Obj>            ");
            AcpiDbDecodeInternalObject (ObjDesc);
            break;
        }
        break;

    default:

        AcpiOsPrintf ("<Not a valid ACPI Object Descriptor> [%s]",
            AcpiUtGetDescriptorName (ObjDesc));
        break;
    }

    AcpiOsPrintf ("\n");
}