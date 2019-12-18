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
typedef  int /*<<< orphan*/  dbl_floating_point ;
typedef  scalar_t__ boolean ;

/* Variables and functions */
 int DBL_BIAS ; 
 int /*<<< orphan*/  Dbl_clear_signexponent_set_hidden (unsigned int) ; 
 int /*<<< orphan*/  Dbl_copyfromptr (int /*<<< orphan*/ *,unsigned int,unsigned int) ; 
 int Dbl_exponent (unsigned int) ; 
 scalar_t__ Dbl_isinexact_to_unsigned (unsigned int,unsigned int,int) ; 
 scalar_t__ Dbl_isnotzero_exponentmantissa (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  Dbl_isnotzero_mantissa (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  Dbl_isone_roundbit (unsigned int,unsigned int,int) ; 
 scalar_t__ Dbl_isone_sign (unsigned int) ; 
 int /*<<< orphan*/  Dbl_isone_stickybit (unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  Dbl_iszero_sign (unsigned int) ; 
 scalar_t__ FALSE ; 
 int INEXACTEXCEPTION ; 
 int INVALIDEXCEPTION ; 
 scalar_t__ Is_inexacttrap_enabled () ; 
 scalar_t__ Is_invalidtrap_enabled () ; 
 int NOEXCEPTION ; 
#define  ROUNDMINUS 130 
#define  ROUNDNEAREST 129 
#define  ROUNDPLUS 128 
 int Rounding_mode () ; 
 int SGL_FX_MAX_EXP ; 
 int /*<<< orphan*/  Set_inexactflag () ; 
 int /*<<< orphan*/  Set_invalidflag () ; 
 int /*<<< orphan*/  Suint_from_dbl_mantissa (unsigned int,unsigned int,int,unsigned int) ; 
 scalar_t__ TRUE ; 

int
dbl_to_sgl_fcnvfu (dbl_floating_point * srcptr, unsigned int *nullptr,
		   unsigned int *dstptr, unsigned int *status)
{
	register unsigned int srcp1, srcp2, result;
	register int src_exponent;
	register boolean inexact = FALSE;

	Dbl_copyfromptr(srcptr,srcp1,srcp2);
	src_exponent = Dbl_exponent(srcp1) - DBL_BIAS;

	/* 
	 * Test for overflow
	 */
	if (src_exponent > SGL_FX_MAX_EXP + 1) {
		if (Dbl_isone_sign(srcp1)) {
			result = 0;
		} else {
			result = 0xffffffff;
		}
		if (Is_invalidtrap_enabled()) {
			return(INVALIDEXCEPTION);
		}
		Set_invalidflag();
		*dstptr = result;
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
			result = 0;
			if (Is_invalidtrap_enabled()) {
				return(INVALIDEXCEPTION);
			}
			Set_invalidflag();
			*dstptr = result;
			return(NOEXCEPTION);
		}
		Dbl_clear_signexponent_set_hidden(srcp1);
		Suint_from_dbl_mantissa(srcp1,srcp2,src_exponent,result);

		/* check for inexact */
		if (Dbl_isinexact_to_unsigned(srcp1,srcp2,src_exponent)) {
			inexact = TRUE;
			/*  round result  */
			switch (Rounding_mode()) {
			case ROUNDPLUS:
			     result++;
			     break;
			case ROUNDMINUS: /* never negative */
			     break;
			case ROUNDNEAREST:
			     if(Dbl_isone_roundbit(srcp1,srcp2,src_exponent) &&
				(Dbl_isone_stickybit(srcp1,srcp2,src_exponent)||
				 result&1))
				   result++;
			     break;
			}
			/* check for overflow */
			if (result == 0) {
				result = 0xffffffff;
				if (Is_invalidtrap_enabled()) {
					return(INVALIDEXCEPTION);
				}
				Set_invalidflag();
				*dstptr = result;
				return(NOEXCEPTION);
			}
		}
	} else {
		result = 0;

		/* check for inexact */
		if (Dbl_isnotzero_exponentmantissa(srcp1,srcp2)) {
			inexact = TRUE;
			/*  round result  */
			switch (Rounding_mode()) {
			case ROUNDPLUS:
				if (Dbl_iszero_sign(srcp1)) result++;
				break;
			case ROUNDMINUS:
				if (Dbl_isone_sign(srcp1)) {
					result = 0;
					if (Is_invalidtrap_enabled()) {
						return(INVALIDEXCEPTION);
					}
					Set_invalidflag();
					inexact = FALSE;
				}
				break;
			case ROUNDNEAREST:
				if (src_exponent == -1 &&
				    Dbl_isnotzero_mantissa(srcp1,srcp2))
					if (Dbl_isone_sign(srcp1)) {
						result = 0;
						if (Is_invalidtrap_enabled()) {
							return(INVALIDEXCEPTION);
						}
						Set_invalidflag();
						inexact = FALSE;
					}
					else result++;
			}
		}
	}
	*dstptr = result;
	if (inexact) {
		if (Is_inexacttrap_enabled()) return(INEXACTEXCEPTION);
		else Set_inexactflag();
	}
	return(NOEXCEPTION);
}