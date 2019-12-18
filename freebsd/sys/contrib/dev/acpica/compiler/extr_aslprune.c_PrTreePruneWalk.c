#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_9__ ;
typedef  struct TYPE_32__   TYPE_8__ ;
typedef  struct TYPE_31__   TYPE_7__ ;
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;
typedef  struct TYPE_24__   TYPE_16__ ;
typedef  struct TYPE_23__   TYPE_15__ ;
typedef  struct TYPE_22__   TYPE_14__ ;
typedef  struct TYPE_21__   TYPE_13__ ;
typedef  struct TYPE_20__   TYPE_12__ ;
typedef  struct TYPE_19__   TYPE_11__ ;
typedef  struct TYPE_18__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ UINT32 ;
struct TYPE_33__ {TYPE_8__* Next; } ;
struct TYPE_31__ {TYPE_6__* Next; } ;
struct TYPE_32__ {TYPE_7__ Asl; } ;
struct TYPE_29__ {TYPE_4__* Next; } ;
struct TYPE_30__ {TYPE_5__ Asl; } ;
struct TYPE_27__ {TYPE_2__* Next; } ;
struct TYPE_28__ {TYPE_3__ Asl; } ;
struct TYPE_25__ {int /*<<< orphan*/ * Next; } ;
struct TYPE_26__ {TYPE_1__ Asl; } ;
struct TYPE_22__ {scalar_t__ ParseOpcode; TYPE_13__* Child; } ;
struct TYPE_24__ {TYPE_14__ Asl; } ;
struct TYPE_23__ {scalar_t__ PruneLevel; scalar_t__ ParseOpcode; int /*<<< orphan*/  Count; } ;
struct TYPE_18__ {char* Name; } ;
struct TYPE_20__ {TYPE_11__* Next; TYPE_10__ Value; } ;
struct TYPE_21__ {TYPE_12__ Asl; } ;
struct TYPE_19__ {TYPE_9__ Asl; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_15__ ACPI_PRUNE_INFO ;
typedef  TYPE_16__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*) ; 
#define  PARSEOP_DEVICE 131 
#define  PARSEOP_ELSE 130 
#define  PARSEOP_IF 129 
#define  PARSEOP_METHOD 128 
 int /*<<< orphan*/  PrPrintObjectAtLevel (scalar_t__,char*) ; 

__attribute__((used)) static ACPI_STATUS
PrTreePruneWalk (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  Level,
    void                    *Context)
{
    ACPI_PRUNE_INFO         *PruneObj = (ACPI_PRUNE_INFO *) Context;


    /* We only care about objects below the Prune Level threshold */

    if (Level <= PruneObj->PruneLevel)
    {
        return (AE_OK);
    }

    if ((Op->Asl.ParseOpcode != PruneObj->ParseOpcode) &&
       !(Op->Asl.ParseOpcode == PARSEOP_ELSE &&
             PruneObj->ParseOpcode == PARSEOP_IF))
    {
        return (AE_OK);
    }

    switch (Op->Asl.ParseOpcode)
    {
    case PARSEOP_METHOD:

        AcpiOsPrintf ("Method");
        PrPrintObjectAtLevel (Level, Op->Asl.Child->Asl.Value.Name);
        Op->Asl.Child->Asl.Next->Asl.Next->Asl.Next->Asl.Next->Asl.Next->Asl.Next = NULL;
        PruneObj->Count++;
        break;

    case PARSEOP_DEVICE:

        AcpiOsPrintf ("Device");
        PrPrintObjectAtLevel (Level, Op->Asl.Child->Asl.Value.Name);
        Op->Asl.Child->Asl.Next = NULL;
        PruneObj->Count++;
        break;

    case PARSEOP_IF:
    case PARSEOP_ELSE:

        if (Op->Asl.ParseOpcode == PARSEOP_ELSE)
        {
            PrPrintObjectAtLevel(Level, "Else");
            Op->Asl.Child = NULL;
        }
        else
        {
            PrPrintObjectAtLevel(Level, "If");
            Op->Asl.Child->Asl.Next = NULL;
        }

        PruneObj->Count++;
        break;

    default:

        break;
    }

    return (AE_OK);
}