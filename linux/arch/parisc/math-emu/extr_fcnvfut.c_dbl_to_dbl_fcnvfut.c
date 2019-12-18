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
typedef  int /*<<< orphan*/  dbl_unsigned ;
typedef  int /*<<< orphan*/  dbl_floating_point ;

/* Variables and functions */
 int DBL_BIAS ; 
 int DBL_FX_MAX_EXP ; 
 int /*<<< orphan*/  Dbl_clear_signexponent_set_hidden (unsigned int) ; 
 int /*<<< orphan*/  Dbl_copyfromptr (int /*<<< orphan*/ *,unsigned int,unsigned int) ; 
 int Dbl_exponent (unsigned int) ; 
 scalar_t__ Dbl_isinexact_to_unsigned (unsigned int,unsigned int,int) ; 
 scalar_t__ Dbl_isnotzero_exponentmantissa (unsigned int,unsigned int) ; 
 scalar_t__ Dbl_isone_sign (unsigned int) ; 
 int /*<<< orphan*/  Duint_copytoptr (unsigned int,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Duint_from_dbl_mantissa (unsigned int,unsigned int,int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  Duint_setzero (unsigned int,unsigned int) ; 
 int INEXACTEXCEPTION ; 
 int INVALIDEXCEPTION ; 
 scalar_t__ Is_inexacttrap_enabled () ; 
 scalar_t__ Is_invalidtrap_enabled () ; 
 int NOEXCEPTION ; 
 int /*<<< orphan*/  Set_inexactflag () ; 
 int /*<<< orphan*/  Set_invalidflag () ; 

int
dbl_to_dbl_fcnvfut (dbl_floating_point * srcptr, unsigned int *nullptr,
		    dbl_unsigned * dstptr, unsigned int *status)
{
	register int src_exponent;
	register unsigned int srcp1, srcp2, resultp1, resultp2;

	Dbl_copyfromptr(srcptr,srcp1,srcp2);
	src_exponent = Dbl_exponent(srcp1) - DBL_BIAS;

	/* 
	 * Test for overflow
	 */
	if (src_exponent > DBL_FX_MAX_EXP + 1) {
		if (Dbl_isone_sign(srcp1)) {
			resultp1 = resultp2 = 0;
		} else {
			resultp1 = resultp2 = 0xffffffff;
		}
		if (Is_invalidtrap_enabled()) {
			return(INVALIDEXCEPTION);
		}
		Set_invalidflag();
    		Duint_copytoptr(resultp1,resultp2,dstptr);
		return(NOEXCEPTION);
	}
	/*
	 * Generate result
	 */
	if (src_exponent >= 0) {
		/* 
		 * Check sign.
		 * If negative, trap unimplemented.
		 */
		if (Dbl_isone_sign(srcp1)) {
			resultp1 = resultp2 = 0;
			if (Is_invalidtrap_enabled()) {
				return(INVALIDEXCEPTION);
			}
			Set_invalidflag();
    			Duint_copytoptr(resultp1,resultp2,dstptr);
			return(NOEXCEPTION);
		}
		Dbl_clear_signexponent_set_hidden(srcp1);
		Duint_from_dbl_mantissa(srcp1,srcp2,src_exponent,
		  resultp1,resultp2);
		Duint_copytoptr(resultp1,resultp2,dstptr);

		/* check for inexact */
		if (Dbl_isinexact_to_unsigned(srcp1,srcp2,src_exponent)) {
			if (Is_inexacttrap_enabled()) return(INEXACTEXCEPTION);
			else Set_inexactflag();
		}
	}
	else {
		Duint_setzero(resultp1,resultp2);
		Duint_copytoptr(resultp1,resultp2,dstptr);

		/* check for inexact */
		if (Dbl_isnotzero_exponentmantissa(srcp1,srcp2)) {
			if (Is_inexacttrap_enabled()) return(INEXACTEXCEPTION);
			else Set_inexactflag();
		}
	}
	return(NOEXCEPTION);
}