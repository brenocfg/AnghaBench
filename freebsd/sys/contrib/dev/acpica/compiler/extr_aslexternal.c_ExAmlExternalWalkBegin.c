#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_8__ {int /*<<< orphan*/  Arg; } ;
struct TYPE_10__ {scalar_t__ ParseOpcode; TYPE_4__* Parent; TYPE_1__ Value; } ;
struct TYPE_12__ {TYPE_3__ Asl; } ;
struct TYPE_9__ {scalar_t__ ParseOpcode; } ;
struct TYPE_11__ {TYPE_2__ Asl; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_5__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AslGbl_ExternalsListHead ; 
 int /*<<< orphan*/  ExInsertArgCount (TYPE_5__*) ; 
 scalar_t__ PARSEOP_DEFINITION_BLOCK ; 
 scalar_t__ PARSEOP_EXTERNAL ; 
 scalar_t__ PARSEOP_METHODCALL ; 

ACPI_STATUS
ExAmlExternalWalkBegin (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  Level,
    void                    *Context)
{

    /* External list head saved in the definition block op */

    if (Op->Asl.ParseOpcode == PARSEOP_DEFINITION_BLOCK)
    {
        AslGbl_ExternalsListHead = Op->Asl.Value.Arg;
    }

    if (!AslGbl_ExternalsListHead)
    {
        return (AE_OK);
    }

    if (Op->Asl.ParseOpcode != PARSEOP_METHODCALL)
    {
        return (AE_OK);
    }

    /*
     * The NameOp child under an ExternalOp gets turned into PARSE_METHODCALL
     * by XfNamespaceLocateBegin(). Ignore these.
     */
    if (Op->Asl.Parent &&
        Op->Asl.Parent->Asl.ParseOpcode == PARSEOP_EXTERNAL)
    {
        return (AE_OK);
    }

    ExInsertArgCount (Op);
    return (AE_OK);
}