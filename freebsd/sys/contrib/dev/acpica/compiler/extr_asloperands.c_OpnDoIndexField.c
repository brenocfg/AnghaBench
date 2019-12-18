#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* Next; TYPE_2__* Child; } ;
struct TYPE_7__ {TYPE_1__ Asl; } ;
typedef  TYPE_2__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  OpnDoFieldCommon (TYPE_2__*,TYPE_2__*) ; 

__attribute__((used)) static void
OpnDoIndexField (
    ACPI_PARSE_OBJECT       *Op)
{
    ACPI_PARSE_OBJECT       *Next;


    /* Opcode is parent node */
    /* First child is the index name */

    Next = Op->Asl.Child;

    /* Second child is the data name */

    Next = Next->Asl.Next;

    /* Third child is the AccessType */

    OpnDoFieldCommon (Op, Next->Asl.Next);
}