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

/* Variables and functions */
#define  P_ADD 149 
#define  P_BIN_AND 148 
#define  P_BIN_NOT 147 
#define  P_BIN_OR 146 
#define  P_BIN_XOR 145 
#define  P_COLON 144 
#define  P_DIV 143 
#define  P_LOGIC_AND 142 
#define  P_LOGIC_EQ 141 
#define  P_LOGIC_GEQ 140 
#define  P_LOGIC_GREATER 139 
#define  P_LOGIC_LEQ 138 
#define  P_LOGIC_LESS 137 
#define  P_LOGIC_NOT 136 
#define  P_LOGIC_OR 135 
#define  P_LOGIC_UNEQ 134 
#define  P_LSHIFT 133 
#define  P_MOD 132 
#define  P_MUL 131 
#define  P_QUESTIONMARK 130 
#define  P_RSHIFT 129 
#define  P_SUB 128 
 int qfalse ; 

int PC_OperatorPriority(int op)
{
	switch(op)
	{
		case P_MUL: return 15;
		case P_DIV: return 15;
		case P_MOD: return 15;
		case P_ADD: return 14;
		case P_SUB: return 14;

		case P_LOGIC_AND: return 7;
		case P_LOGIC_OR: return 6;
		case P_LOGIC_GEQ: return 12;
		case P_LOGIC_LEQ: return 12;
		case P_LOGIC_EQ: return 11;
		case P_LOGIC_UNEQ: return 11;

		case P_LOGIC_NOT: return 16;
		case P_LOGIC_GREATER: return 12;
		case P_LOGIC_LESS: return 12;

		case P_RSHIFT: return 13;
		case P_LSHIFT: return 13;

		case P_BIN_AND: return 10;
		case P_BIN_OR: return 8;
		case P_BIN_XOR: return 9;
		case P_BIN_NOT: return 16;

		case P_COLON: return 5;
		case P_QUESTIONMARK: return 5;
	} //end switch
	return qfalse;
}