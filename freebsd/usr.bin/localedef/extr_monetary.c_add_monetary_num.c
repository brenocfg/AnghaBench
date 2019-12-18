#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* int_frac_digits; char* frac_digits; char* p_cs_precedes; char* p_sep_by_space; char* n_cs_precedes; char* n_sep_by_space; char* p_sign_posn; char* n_sign_posn; char* int_p_cs_precedes; char* int_n_cs_precedes; char* int_p_sep_by_space; char* int_n_sep_by_space; char* int_p_sign_posn; char* int_n_sign_posn; char* mon_grouping; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTERR ; 
#define  T_FRAC_DIGITS 142 
#define  T_INT_FRAC_DIGITS 141 
#define  T_INT_N_CS_PRECEDES 140 
#define  T_INT_N_SEP_BY_SPACE 139 
#define  T_INT_N_SIGN_POSN 138 
#define  T_INT_P_CS_PRECEDES 137 
#define  T_INT_P_SEP_BY_SPACE 136 
#define  T_INT_P_SIGN_POSN 135 
#define  T_MON_GROUPING 134 
#define  T_N_CS_PRECEDES 133 
#define  T_N_SEP_BY_SPACE 132 
#define  T_N_SIGN_POSN 131 
#define  T_P_CS_PRECEDES 130 
#define  T_P_SEP_BY_SPACE 129 
#define  T_P_SIGN_POSN 128 
 int /*<<< orphan*/  asprintf (char**,char*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int last_kw ; 
 TYPE_1__ mon ; 
 int /*<<< orphan*/  stderr ; 

void
add_monetary_num(int n)
{
	char *str = NULL;

	(void) asprintf(&str, "%d", n);
	if (str == NULL) {
		fprintf(stderr, "out of memory");
		return;
	}

	switch (last_kw) {
	case T_INT_FRAC_DIGITS:
		mon.int_frac_digits = str;
		break;
	case T_FRAC_DIGITS:
		mon.frac_digits = str;
		break;
	case T_P_CS_PRECEDES:
		mon.p_cs_precedes = str;
		break;
	case T_P_SEP_BY_SPACE:
		mon.p_sep_by_space = str;
		break;
	case T_N_CS_PRECEDES:
		mon.n_cs_precedes = str;
		break;
	case T_N_SEP_BY_SPACE:
		mon.n_sep_by_space = str;
		break;
	case T_P_SIGN_POSN:
		mon.p_sign_posn = str;
		break;
	case T_N_SIGN_POSN:
		mon.n_sign_posn = str;
		break;
	case T_INT_P_CS_PRECEDES:
		mon.int_p_cs_precedes = str;
		break;
	case T_INT_N_CS_PRECEDES:
		mon.int_n_cs_precedes = str;
		break;
	case T_INT_P_SEP_BY_SPACE:
		mon.int_p_sep_by_space = str;
		break;
	case T_INT_N_SEP_BY_SPACE:
		mon.int_n_sep_by_space = str;
		break;
	case T_INT_P_SIGN_POSN:
		mon.int_p_sign_posn = str;
		break;
	case T_INT_N_SIGN_POSN:
		mon.int_n_sign_posn = str;
		break;
	case T_MON_GROUPING:
		mon.mon_grouping = str;
		break;
	default:
		INTERR;
		break;
	}
}