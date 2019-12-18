#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_5__ {scalar_t__ ParseOpcode; int /*<<< orphan*/  ExternalName; int /*<<< orphan*/  Node; } ;
struct TYPE_7__ {TYPE_1__ Asl; } ;
struct TYPE_6__ {TYPE_3__* CurrentOp; } ;
typedef  TYPE_2__ ASL_METHOD_INFO ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_3__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  AE_ALREADY_EXISTS ; 
 int /*<<< orphan*/  AE_CTRL_TERMINATE ; 
 int /*<<< orphan*/  AE_OK ; 
 scalar_t__ PARSEOP_METHODCALL ; 
 scalar_t__ PARSEOP_NAMESEG ; 
 scalar_t__ PARSEOP_NAMESTRING ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ACPI_STATUS
OtXrefAnalysisWalkPart1 (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  Level,
    void                    *Context)
{
    ASL_METHOD_INFO         *MethodInfo = (ASL_METHOD_INFO *) Context;
    ACPI_PARSE_OBJECT       *Next;


    /* Only interested in name string Ops -- ignore all others */

    if ((Op->Asl.ParseOpcode != PARSEOP_NAMESEG) &&
        (Op->Asl.ParseOpcode != PARSEOP_NAMESTRING) &&
        (Op->Asl.ParseOpcode != PARSEOP_METHODCALL))
    {
        return (AE_OK);
    }

    /* No node means a locally declared object -- ignore */

    if (!Op->Asl.Node)
    {
        return (AE_OK);
    }

    /* When we encounter the source Op, we are done */

    Next = MethodInfo->CurrentOp;
    if (Next == Op)
    {
        return (AE_CTRL_TERMINATE);
    }

    /* If we have a name match, this Op is a duplicate */

    if ((Next->Asl.ParseOpcode == PARSEOP_NAMESEG)      ||
        (Next->Asl.ParseOpcode == PARSEOP_NAMESTRING)   ||
        (Next->Asl.ParseOpcode == PARSEOP_METHODCALL))
    {
        if (!strcmp (Op->Asl.ExternalName, Next->Asl.ExternalName))
        {
            return (AE_ALREADY_EXISTS);
        }
    }

    return (AE_OK);
}