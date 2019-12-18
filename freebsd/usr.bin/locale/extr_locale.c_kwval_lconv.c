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
struct lconv {char* int_curr_symbol; char* currency_symbol; char* mon_decimal_point; char* mon_thousands_sep; char* positive_sign; char* negative_sign; char int_frac_digits; char frac_digits; char p_cs_precedes; char p_sep_by_space; char n_cs_precedes; char n_sep_by_space; char p_sign_posn; char n_sign_posn; char int_p_cs_precedes; char int_p_sep_by_space; char int_n_cs_precedes; char int_n_sep_by_space; char int_p_sign_posn; char int_n_sign_posn; int /*<<< orphan*/  mon_grouping; int /*<<< orphan*/  grouping; } ;

/* Variables and functions */
#define  KW_CURRENCY_SYMBOL 149 
#define  KW_FRAC_DIGITS 148 
#define  KW_GROUPING 147 
#define  KW_INT_CURR_SYMBOL 146 
#define  KW_INT_FRAC_DIGITS 145 
#define  KW_INT_N_CS_PRECEDES 144 
#define  KW_INT_N_SEP_BY_SPACE 143 
#define  KW_INT_N_SIGN_POSN 142 
#define  KW_INT_P_CS_PRECEDES 141 
#define  KW_INT_P_SEP_BY_SPACE 140 
#define  KW_INT_P_SIGN_POSN 139 
#define  KW_MON_DECIMAL_POINT 138 
#define  KW_MON_GROUPING 137 
#define  KW_MON_THOUSANDS_SEP 136 
#define  KW_NEGATIVE_SIGN 135 
#define  KW_N_CS_PRECEDES 134 
#define  KW_N_SEP_BY_SPACE 133 
#define  KW_N_SIGN_POSN 132 
#define  KW_POSITIVE_SIGN 131 
#define  KW_P_CS_PRECEDES 130 
#define  KW_P_SEP_BY_SPACE 129 
#define  KW_P_SIGN_POSN 128 
 char* format_grouping (int /*<<< orphan*/ ) ; 
 struct lconv* localeconv () ; 

char *
kwval_lconv(int id)
{
	struct lconv *lc;
	char *rval;

	rval = NULL;
	lc = localeconv();
	switch (id) {
		case KW_GROUPING:
			rval = format_grouping(lc->grouping);
			break;
		case KW_INT_CURR_SYMBOL:
			rval = lc->int_curr_symbol;
			break;
		case KW_CURRENCY_SYMBOL:
			rval = lc->currency_symbol;
			break;
		case KW_MON_DECIMAL_POINT:
			rval = lc->mon_decimal_point;
			break;
		case KW_MON_THOUSANDS_SEP:
			rval = lc->mon_thousands_sep;
			break;
		case KW_MON_GROUPING:
			rval = format_grouping(lc->mon_grouping);
			break;
		case KW_POSITIVE_SIGN:
			rval = lc->positive_sign;
			break;
		case KW_NEGATIVE_SIGN:
			rval = lc->negative_sign;
			break;
		case KW_INT_FRAC_DIGITS:
			rval = &(lc->int_frac_digits);
			break;
		case KW_FRAC_DIGITS:
			rval = &(lc->frac_digits);
			break;
		case KW_P_CS_PRECEDES:
			rval = &(lc->p_cs_precedes);
			break;
		case KW_P_SEP_BY_SPACE:
			rval = &(lc->p_sep_by_space);
			break;
		case KW_N_CS_PRECEDES:
			rval = &(lc->n_cs_precedes);
			break;
		case KW_N_SEP_BY_SPACE:
			rval = &(lc->n_sep_by_space);
			break;
		case KW_P_SIGN_POSN:
			rval = &(lc->p_sign_posn);
			break;
		case KW_N_SIGN_POSN:
			rval = &(lc->n_sign_posn);
			break;
		case KW_INT_P_CS_PRECEDES:
			rval = &(lc->int_p_cs_precedes);
			break;
		case KW_INT_P_SEP_BY_SPACE:
			rval = &(lc->int_p_sep_by_space);
			break;
		case KW_INT_N_CS_PRECEDES:
			rval = &(lc->int_n_cs_precedes);
			break;
		case KW_INT_N_SEP_BY_SPACE:
			rval = &(lc->int_n_sep_by_space);
			break;
		case KW_INT_P_SIGN_POSN:
			rval = &(lc->int_p_sign_posn);
			break;
		case KW_INT_N_SIGN_POSN:
			rval = &(lc->int_n_sign_posn);
			break;
		default:
			break;
	}
	return (rval);
}