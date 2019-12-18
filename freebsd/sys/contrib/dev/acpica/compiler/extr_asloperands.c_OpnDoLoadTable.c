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
struct TYPE_6__ {char* String; } ;
struct TYPE_7__ {scalar_t__ ParseOpcode; int AmlLength; TYPE_3__* Next; TYPE_1__ Value; TYPE_3__* Child; } ;
struct TYPE_8__ {TYPE_2__ Asl; } ;
typedef  TYPE_3__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 scalar_t__ DEFAULT_ARG ; 
 int /*<<< orphan*/  OpcGenerateAmlOpcode (TYPE_3__*) ; 
 scalar_t__ PARSEOP_STRING_LITERAL ; 
 scalar_t__ PARSEOP_ZERO ; 
 void* ZERO ; 

__attribute__((used)) static void
OpnDoLoadTable (
    ACPI_PARSE_OBJECT       *Op)
{
    ACPI_PARSE_OBJECT       *Next;


    /* Opcode is parent node */
    /* First child is the table signature */

    Next = Op->Asl.Child;

    /* Second child is the OEM ID*/

    Next = Next->Asl.Next;

    /* Third child is the OEM table ID */

    Next = Next->Asl.Next;

    /* Fourth child is the RootPath string */

    Next = Next->Asl.Next;
    if (Next->Asl.ParseOpcode == PARSEOP_ZERO)
    {
        Next->Asl.ParseOpcode = PARSEOP_STRING_LITERAL;
        Next->Asl.Value.String = "\\";
        Next->Asl.AmlLength = 2;
        OpcGenerateAmlOpcode (Next);
    }

#ifdef ASL_FUTURE_IMPLEMENTATION

    /* TBD: NOT IMPLEMENTED */
    /* Fifth child is the [optional] ParameterPathString */
    /* Sixth child is the [optional] ParameterData */

    Next = Next->Asl.Next;
    if (Next->Asl.ParseOpcode == DEFAULT_ARG)
    {
        Next->Asl.AmlLength = 1;
        Next->Asl.ParseOpcode = ZERO;
        OpcGenerateAmlOpcode (Next);
    }


    Next = Next->Asl.Next;
    if (Next->Asl.ParseOpcode == DEFAULT_ARG)
    {
        Next->Asl.AmlLength = 1;
        Next->Asl.ParseOpcode = ZERO;
        OpcGenerateAmlOpcode (Next);
    }
#endif
}