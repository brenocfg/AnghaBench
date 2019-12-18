#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int UINT16 ;

/* Variables and functions */
#define  AML_ADD_OP 137 
#define  AML_BIT_AND_OP 136 
#define  AML_BIT_OR_OP 135 
#define  AML_BIT_XOR_OP 134 
#define  AML_DIVIDE_OP 133 
#define  AML_MOD_OP 132 
#define  AML_MULTIPLY_OP 131 
#define  AML_SHIFT_LEFT_OP 130 
#define  AML_SHIFT_RIGHT_OP 129 
#define  AML_SUBTRACT_OP 128 

__attribute__((used)) static char *
AcpiDmGetCompoundSymbol (
   UINT16                   AmlOpcode)
{
    char                    *Symbol;


    switch (AmlOpcode)
    {
    case AML_ADD_OP:
        Symbol = " += ";
        break;

    case AML_SUBTRACT_OP:
        Symbol = " -= ";
        break;

    case AML_MULTIPLY_OP:
        Symbol = " *= ";
        break;

    case AML_DIVIDE_OP:
        Symbol = " /= ";
        break;

    case AML_MOD_OP:
        Symbol = " %= ";
        break;

    case AML_SHIFT_LEFT_OP:
        Symbol = " <<= ";
        break;

    case AML_SHIFT_RIGHT_OP:
        Symbol = " >>= ";
        break;

    case AML_BIT_AND_OP:
        Symbol = " &= ";
        break;

    case AML_BIT_OR_OP:
        Symbol = " |= ";
        break;

    case AML_BIT_XOR_OP:
        Symbol = " ^= ";
        break;

    default:

        /* No operator string for all other opcodes */

        return (NULL);
    }

    return (Symbol);
}