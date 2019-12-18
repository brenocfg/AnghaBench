#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT32 ;
struct TYPE_12__ {TYPE_2__* Op; } ;
struct TYPE_11__ {char* Name; } ;
struct TYPE_9__ {int CompileFlags; int /*<<< orphan*/  ExternalName; TYPE_4__* Node; } ;
struct TYPE_10__ {TYPE_1__ Asl; } ;
typedef  TYPE_2__ ACPI_PARSE_OBJECT ;
typedef  TYPE_3__ ACPI_OPCODE_INFO ;
typedef  TYPE_4__ ACPI_NAMESPACE_NODE ;

/* Variables and functions */
 int /*<<< orphan*/  ASL_ERROR ; 
 int /*<<< orphan*/  ASL_MSG_INVALID_TYPE ; 
 int /*<<< orphan*/  ASL_MSG_NO_RETVAL ; 
 int /*<<< orphan*/  ASL_MSG_SOME_NO_RETVAL ; 
 int /*<<< orphan*/  ASL_WARNING ; 
 int /*<<< orphan*/  AnFormatBtype (char*,int) ; 
 int /*<<< orphan*/  AslError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AslGbl_MsgBuffer ; 
 char* AslGbl_StringBuffer ; 
 char* AslGbl_StringBuffer2 ; 
 int OP_METHOD_NO_RETVAL ; 
 int OP_METHOD_SOME_NO_RETVAL ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*,char*,char*) ; 

void
AnCheckMethodReturnValue (
    ACPI_PARSE_OBJECT       *Op,
    const ACPI_OPCODE_INFO  *OpInfo,
    ACPI_PARSE_OBJECT       *ArgOp,
    UINT32                  RequiredBtypes,
    UINT32                  ThisNodeBtype)
{
    ACPI_PARSE_OBJECT       *OwningOp;
    ACPI_NAMESPACE_NODE     *Node;


    Node = ArgOp->Asl.Node;

    if (!Node)
    {
        /* No error message, this can happen and is OK */

        return;
    }

    /* Examine the parent op of this method */

    OwningOp = Node->Op;
    if (OwningOp->Asl.CompileFlags & OP_METHOD_NO_RETVAL)
    {
        /* Method NEVER returns a value */

        AslError (ASL_ERROR, ASL_MSG_NO_RETVAL, Op, Op->Asl.ExternalName);
    }
    else if (OwningOp->Asl.CompileFlags & OP_METHOD_SOME_NO_RETVAL)
    {
        /* Method SOMETIMES returns a value, SOMETIMES not */

        AslError (ASL_WARNING, ASL_MSG_SOME_NO_RETVAL,
            Op, Op->Asl.ExternalName);
    }
    else if (!(ThisNodeBtype & RequiredBtypes))
    {
        /* Method returns a value, but the type is wrong */

        AnFormatBtype (AslGbl_StringBuffer, ThisNodeBtype);
        AnFormatBtype (AslGbl_StringBuffer2, RequiredBtypes);

        /*
         * The case where the method does not return any value at all
         * was already handled in the namespace cross reference
         * -- Only issue an error if the method in fact returns a value,
         * but it is of the wrong type
         */
        if (ThisNodeBtype != 0)
        {
            sprintf (AslGbl_MsgBuffer,
                "Method returns [%s], %s operator requires [%s]",
                AslGbl_StringBuffer, OpInfo->Name, AslGbl_StringBuffer2);

            AslError (ASL_ERROR, ASL_MSG_INVALID_TYPE, ArgOp, AslGbl_MsgBuffer);
        }
    }
}