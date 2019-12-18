#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  Peer; int /*<<< orphan*/  Child; int /*<<< orphan*/  Parent; int /*<<< orphan*/  Flags; int /*<<< orphan*/  SizeOfLengthField; int /*<<< orphan*/  TotalLength; int /*<<< orphan*/  Length; int /*<<< orphan*/  Name; int /*<<< orphan*/  Depth; } ;
typedef  TYPE_1__ DT_SUBTABLE ;

/* Variables and functions */
 int /*<<< orphan*/  ASL_DEBUG_OUTPUT ; 
 int /*<<< orphan*/  DbgPrint (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
DtDumpSubtableInfo (
    DT_SUBTABLE             *Subtable,
    void                    *Context,
    void                    *ReturnValue)
{

    DbgPrint (ASL_DEBUG_OUTPUT,
        "[%.04X] %24s %.08X %.08X %.08X %.08X %p %p %p %p\n",
        Subtable->Depth, Subtable->Name, Subtable->Length, Subtable->TotalLength,
        Subtable->SizeOfLengthField, Subtable->Flags, Subtable,
        Subtable->Parent, Subtable->Child, Subtable->Peer);
}