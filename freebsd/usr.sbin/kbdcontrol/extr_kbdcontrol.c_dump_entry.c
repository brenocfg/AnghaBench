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
#define  ALK 157 
#define  ASH 156 
#define  BTAB 155 
#define  CLK 154 
#define  DBG 153 
 int F_ACC ; 
 int F_FN ; 
 int F_SCR ; 
#define  HALT 152 
#define  LALT 151 
#define  LALTA 150 
#define  LCTR 149 
#define  LCTRA 148 
#define  LSH 147 
#define  LSHA 146 
 int L_ACC ; 
 int L_FN ; 
 int L_SCR ; 
#define  META 145 
#define  NEXT 144 
#define  NLK 143 
#define  NOP 142 
#define  PASTE 141 
#define  PDWN 140 
#define  PNC 139 
#define  PREV 138 
#define  RALT 137 
#define  RALTA 136 
#define  RBT 135 
#define  RCTR 134 
#define  RCTRA 133 
#define  RSH 132 
#define  RSHA 131 
#define  SLK 130 
 int SPECIAL ; 
#define  SPSC 129 
#define  SUSP 128 
 char** acc_names_u ; 
 scalar_t__ isascii (int) ; 
 scalar_t__ isprint (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
dump_entry(int value)
{
	if (value & SPECIAL) {
		value &= ~SPECIAL;
		switch (value) {
		case NOP:
			printf("  NOP, ");
			break;
		case LSH:
			printf("  LSH, ");
			break;
		case RSH:
			printf("  RSH, ");
			break;
		case CLK:
			printf("  CLK, ");
			break;
		case NLK:
			printf("  NLK, ");
			break;
		case SLK:
			printf("  SLK, ");
			break;
		case BTAB:
			printf(" BTAB, ");
			break;
		case LALT:
			printf(" LALT, ");
			break;
		case LCTR:
			printf(" LCTR, ");
			break;
		case NEXT:
			printf(" NEXT, ");
			break;
		case PREV:
			printf(" PREV, ");
			break;
		case RCTR:
			printf(" RCTR, ");
			break;
		case RALT:
			printf(" RALT, ");
			break;
		case ALK:
			printf("  ALK, ");
			break;
		case ASH:
			printf("  ASH, ");
			break;
		case META:
			printf(" META, ");
			break;
		case RBT:
			printf("  RBT, ");
			break;
		case DBG:
			printf("  DBG, ");
			break;
		case SUSP:
			printf(" SUSP, ");
			break;
		case SPSC:
			printf(" SPSC, ");
			break;
		case PNC:
			printf("  PNC, ");
			break;
		case LSHA:
			printf(" LSHA, ");
			break;
		case RSHA:
			printf(" RSHA, ");
			break;
		case LCTRA:
			printf("LCTRA, ");
			break;
		case RCTRA:
			printf("RCTRA, ");
			break;
		case LALTA:
			printf("LALTA, ");
			break;
		case RALTA:
			printf("RALTA, ");
			break;
		case HALT:
			printf(" HALT, ");
			break;
		case PDWN:
			printf(" PDWN, ");
			break;
		case PASTE:
			printf("PASTE, ");
			break;
		default:
	 		if (value >= F_FN && value <= L_FN)
				printf(" F(%2d),", value - F_FN + 1);
	 		else if (value >= F_SCR && value <= L_SCR)
				printf(" S(%2d),", value - F_SCR + 1);
	 		else if (value >= F_ACC && value <= L_ACC)
				printf(" %-4s, ", acc_names_u[value - F_ACC]);
			else
				printf(" 0x%02X, ", value);
			break;
		}
	} else if (value == '\'') {
		printf(" '\\'', ");
	} else if (value == '\\') {
		printf(" '\\\\', ");
	} else if (isascii(value) && isprint(value)) {
		printf("  '%c', ", value);
	} else {
		printf(" 0x%02X, ", value);
	}
}