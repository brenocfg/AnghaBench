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
struct lconv {char int_n_cs_precedes; char int_n_sep_by_space; char int_n_sign_posn; char* negative_sign; char int_p_cs_precedes; char int_p_sep_by_space; char int_p_sign_posn; char* positive_sign; char n_cs_precedes; char n_sep_by_space; char n_sign_posn; char p_cs_precedes; char p_sep_by_space; char p_sign_posn; } ;

/* Variables and functions */
 char CHAR_MAX ; 
 int IS_NEGATIVE ; 
 int PARENTH_POSN ; 
 int USE_INTL_CURRENCY ; 
 struct lconv* localeconv () ; 

__attribute__((used)) static void
__setup_vars(int flags, char *cs_precedes, char *sep_by_space,
		char *sign_posn, char **signstr) {

	struct lconv *lc = localeconv();

	if ((flags & IS_NEGATIVE) && (flags & USE_INTL_CURRENCY)) {
		*cs_precedes = lc->int_n_cs_precedes;
		*sep_by_space = lc->int_n_sep_by_space;
		*sign_posn = (flags & PARENTH_POSN) ? 0 : lc->int_n_sign_posn;
		*signstr = (lc->negative_sign[0] == '\0') ? "-"
		    : lc->negative_sign;
	} else if (flags & USE_INTL_CURRENCY) {
		*cs_precedes = lc->int_p_cs_precedes;
		*sep_by_space = lc->int_p_sep_by_space;
		*sign_posn = (flags & PARENTH_POSN) ? 0 : lc->int_p_sign_posn;
		*signstr = lc->positive_sign;
	} else if (flags & IS_NEGATIVE) {
		*cs_precedes = lc->n_cs_precedes;
		*sep_by_space = lc->n_sep_by_space;
		*sign_posn = (flags & PARENTH_POSN) ? 0 : lc->n_sign_posn;
		*signstr = (lc->negative_sign[0] == '\0') ? "-"
		    : lc->negative_sign;
	} else {
		*cs_precedes = lc->p_cs_precedes;
		*sep_by_space = lc->p_sep_by_space;
		*sign_posn = (flags & PARENTH_POSN) ? 0 : lc->p_sign_posn;
		*signstr = lc->positive_sign;
	}

	/* Set defult values for unspecified information. */
	if (*cs_precedes != 0)
		*cs_precedes = 1;
	if (*sep_by_space == CHAR_MAX)
		*sep_by_space = 0;
	if (*sign_posn == CHAR_MAX)
		*sign_posn = 0;
}