#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT32 ;
struct TYPE_3__ {void* Flags; int /*<<< orphan*/  Value; struct TYPE_3__* Next; } ;
typedef  TYPE_1__ DT_FIELD ;

/* Variables and functions */
 int /*<<< orphan*/  ASL_CREATOR_ID ; 
 scalar_t__ AslGbl_UseOriginalCompilerId ; 
 void* DT_FIELD_NOT_ALLOCATED ; 
 int /*<<< orphan*/  VersionString ; 

__attribute__((used)) static void
DtInsertCompilerIds (
    DT_FIELD                *FieldList)
{
    DT_FIELD                *Next;
    UINT32                  i;


    /*
     * Don't insert current compiler ID if requested. Used for compiler
     * debug/validation only.
     */
    if (AslGbl_UseOriginalCompilerId)
    {
        return;
    }

    /* Walk to the Compiler fields at the end of the header */

    Next = FieldList;
    for (i = 0; i < 7; i++)
    {
        Next = Next->Next;
    }

    Next->Value = ASL_CREATOR_ID;
    Next->Flags = DT_FIELD_NOT_ALLOCATED;

    Next = Next->Next;
    Next->Value = VersionString;
    Next->Flags = DT_FIELD_NOT_ALLOCATED;
}