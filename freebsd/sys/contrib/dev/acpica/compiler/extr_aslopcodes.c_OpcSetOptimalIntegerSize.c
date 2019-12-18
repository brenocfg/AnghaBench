#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT32 ;
struct TYPE_14__ {int Integer; } ;
struct TYPE_15__ {void* AmlOpcode; TYPE_5__ Value; TYPE_4__* Parent; } ;
struct TYPE_16__ {TYPE_6__ Asl; } ;
struct TYPE_12__ {TYPE_2__* Parent; } ;
struct TYPE_13__ {TYPE_3__ Asl; } ;
struct TYPE_10__ {scalar_t__ ParseOpcode; } ;
struct TYPE_11__ {TYPE_1__ Asl; } ;
typedef  TYPE_7__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int ACPI_UINT16_MAX ; 
#define  ACPI_UINT32_MAX 129 
#define  ACPI_UINT64_MAX 128 
 int ACPI_UINT8_MAX ; 
 void* AML_BYTE_OP ; 
 void* AML_DWORD_OP ; 
 void* AML_ONES_OP ; 
 void* AML_ONE_OP ; 
 void* AML_QWORD_OP ; 
 void* AML_WORD_OP ; 
 void* AML_ZERO_OP ; 
 int /*<<< orphan*/  ASL_MSG_INTEGER_LENGTH ; 
 int /*<<< orphan*/  ASL_MSG_INTEGER_OPTIMIZATION ; 
 int /*<<< orphan*/  ASL_OPTIMIZATION ; 
 int /*<<< orphan*/  ASL_WARNING ; 
 int AcpiGbl_IntegerByteWidth ; 
 int /*<<< orphan*/  AslError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_7__*,char*) ; 
 int /*<<< orphan*/  AslGbl_IgnoreErrors ; 
 scalar_t__ AslGbl_IntegerOptimizationFlag ; 
 scalar_t__ PARSEOP_DEFINITION_BLOCK ; 

UINT32
OpcSetOptimalIntegerSize (
    ACPI_PARSE_OBJECT       *Op)
{

#if 0
    /*
     * TBD: - we don't want to optimize integers in the block header, but the
     * code below does not work correctly.
     */
    if (Op->Asl.Parent &&
        Op->Asl.Parent->Asl.Parent &&
       (Op->Asl.Parent->Asl.Parent->Asl.ParseOpcode == PARSEOP_DEFINITION_BLOCK))
    {
        return (0);
    }
#endif

    /*
     * Check for the special AML integers first - Zero, One, Ones.
     * These are single-byte opcodes that are the smallest possible
     * representation of an integer.
     *
     * This optimization is optional.
     */
    if (AslGbl_IntegerOptimizationFlag)
    {
        switch (Op->Asl.Value.Integer)
        {
        case 0:

            Op->Asl.AmlOpcode = AML_ZERO_OP;
            AslError (ASL_OPTIMIZATION, ASL_MSG_INTEGER_OPTIMIZATION,
                Op, "Zero");
            return (1);

        case 1:

            Op->Asl.AmlOpcode = AML_ONE_OP;
            AslError (ASL_OPTIMIZATION, ASL_MSG_INTEGER_OPTIMIZATION,
                Op, "One");
            return (1);

        case ACPI_UINT32_MAX:

            /* Check for table integer width (32 or 64) */

            if (AcpiGbl_IntegerByteWidth == 4)
            {
                Op->Asl.AmlOpcode = AML_ONES_OP;
                AslError (ASL_OPTIMIZATION, ASL_MSG_INTEGER_OPTIMIZATION,
                    Op, "Ones");
                return (1);
            }
            break;

        case ACPI_UINT64_MAX:

            /* Check for table integer width (32 or 64) */

            if (AcpiGbl_IntegerByteWidth == 8)
            {
                Op->Asl.AmlOpcode = AML_ONES_OP;
                AslError (ASL_OPTIMIZATION, ASL_MSG_INTEGER_OPTIMIZATION,
                    Op, "Ones");
                return (1);
            }
            break;

        default:

            break;
        }
    }

    /* Find the best fit using the various AML integer prefixes */

    if (Op->Asl.Value.Integer <= ACPI_UINT8_MAX)
    {
        Op->Asl.AmlOpcode = AML_BYTE_OP;
        return (1);
    }

    if (Op->Asl.Value.Integer <= ACPI_UINT16_MAX)
    {
        Op->Asl.AmlOpcode = AML_WORD_OP;
        return (2);
    }

    if (Op->Asl.Value.Integer <= ACPI_UINT32_MAX)
    {
        Op->Asl.AmlOpcode = AML_DWORD_OP;
        return (4);
    }
    else /* 64-bit integer */
    {
        if (AcpiGbl_IntegerByteWidth == 4)
        {
            AslError (ASL_WARNING, ASL_MSG_INTEGER_LENGTH,
                Op, NULL);

            if (!AslGbl_IgnoreErrors)
            {
                /* Truncate the integer to 32-bit */

                Op->Asl.Value.Integer &= ACPI_UINT32_MAX;

                /* Now set the optimal integer size */

                return (OpcSetOptimalIntegerSize (Op));
            }
        }

        Op->Asl.AmlOpcode = AML_QWORD_OP;
        return (8);
    }
}