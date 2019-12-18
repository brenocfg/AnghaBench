#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int DisasmFlags; int AmlOpcode; } ;
struct TYPE_6__ {TYPE_1__ Common; } ;
typedef  TYPE_2__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int ACPI_PARSEOP_ASSIGNMENT ; 
 int ACPI_PARSEOP_CLOSING_PAREN ; 
 int ACPI_PARSEOP_COMPOUND_ASSIGNMENT ; 
 int ACPI_PARSEOP_LEGACY_ASL_ONLY ; 
#define  AML_ADD_OP 148 
#define  AML_BIT_AND_OP 147 
#define  AML_BIT_NOT_OP 146 
#define  AML_BIT_OR_OP 145 
#define  AML_BIT_XOR_OP 144 
 int /*<<< orphan*/  AML_COMMENT_END_NODE ; 
#define  AML_DECREMENT_OP 143 
#define  AML_DIVIDE_OP 142 
#define  AML_INCREMENT_OP 141 
#define  AML_INDEX_OP 140 
#define  AML_LOGICAL_AND_OP 139 
#define  AML_LOGICAL_EQUAL_OP 138 
#define  AML_LOGICAL_GREATER_OP 137 
#define  AML_LOGICAL_LESS_OP 136 
#define  AML_LOGICAL_NOT_OP 135 
#define  AML_LOGICAL_OR_OP 134 
#define  AML_MOD_OP 133 
#define  AML_MULTIPLY_OP 132 
#define  AML_SHIFT_LEFT_OP 131 
#define  AML_SHIFT_RIGHT_OP 130 
#define  AML_STORE_OP 129 
#define  AML_SUBTRACT_OP 128 
 int /*<<< orphan*/  ASL_CV_PRINT_ONE_COMMENT (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiGbl_CstyleDisassembly ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*) ; 

void
AcpiDmCloseOperator (
    ACPI_PARSE_OBJECT       *Op)
{

    /* Always emit paren if ASL+ disassembly disabled */

    if (!AcpiGbl_CstyleDisassembly)
    {
        AcpiOsPrintf (")");
        ASL_CV_PRINT_ONE_COMMENT (Op, AML_COMMENT_END_NODE, NULL, 0);
        return;
    }

    if (Op->Common.DisasmFlags & ACPI_PARSEOP_LEGACY_ASL_ONLY)
    {
        AcpiOsPrintf (")");
        ASL_CV_PRINT_ONE_COMMENT (Op, AML_COMMENT_END_NODE, NULL, 0);
        return;
    }

    /* Check if we need to add an additional closing paren */

    switch (Op->Common.AmlOpcode)
    {
    case AML_ADD_OP:
    case AML_SUBTRACT_OP:
    case AML_MULTIPLY_OP:
    case AML_DIVIDE_OP:
    case AML_MOD_OP:
    case AML_SHIFT_LEFT_OP:
    case AML_SHIFT_RIGHT_OP:
    case AML_BIT_AND_OP:
    case AML_BIT_OR_OP:
    case AML_BIT_XOR_OP:
    case AML_LOGICAL_AND_OP:
    case AML_LOGICAL_EQUAL_OP:
    case AML_LOGICAL_GREATER_OP:
    case AML_LOGICAL_LESS_OP:
    case AML_LOGICAL_OR_OP:

        /* Emit paren only if this is not a compound assignment */

        if (Op->Common.DisasmFlags & ACPI_PARSEOP_COMPOUND_ASSIGNMENT)
        {
            ASL_CV_PRINT_ONE_COMMENT (Op, AML_COMMENT_END_NODE, NULL, 0);
            return;
        }

        /* Emit extra close paren for assignment within an expression */

        if (Op->Common.DisasmFlags & ACPI_PARSEOP_ASSIGNMENT)
        {
            AcpiOsPrintf (")");
        }
        break;

    case AML_INDEX_OP:

        /* This is case for unsupported Index() source constants */

        if (Op->Common.DisasmFlags & ACPI_PARSEOP_CLOSING_PAREN)
        {
            AcpiOsPrintf (")");
        }
        ASL_CV_PRINT_ONE_COMMENT (Op, AML_COMMENT_END_NODE, NULL, 0);
        return;

    /* No need for parens for these */

    case AML_DECREMENT_OP:
    case AML_INCREMENT_OP:
    case AML_LOGICAL_NOT_OP:
    case AML_BIT_NOT_OP:
    case AML_STORE_OP:
        ASL_CV_PRINT_ONE_COMMENT (Op, AML_COMMENT_END_NODE, NULL, 0);
        return;

    default:

        /* Always emit paren for non-ASL+ operators */
        break;
    }

    AcpiOsPrintf (")");
    ASL_CV_PRINT_ONE_COMMENT (Op, AML_COMMENT_END_NODE, NULL, 0);

    return;
}