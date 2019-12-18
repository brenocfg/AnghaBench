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
typedef  int /*<<< orphan*/  dbl_integer ;
typedef  int /*<<< orphan*/  dbl_floating_point ;
typedef  scalar_t__ boolean ;

/* Variables and functions */
 int DBL_BIAS ; 
 int DBL_FX_MAX_EXP ; 
 int /*<<< orphan*/  Dbl_clear_signexponent_set_hidden (unsigned int) ; 
 int /*<<< orphan*/  Dbl_copyfromptr (int /*<<< orphan*/ *,unsigned int,unsigned int) ; 
 int Dbl_exponent (unsigned int) ; 
 scalar_t__ Dbl_isinexact_to_fix (unsigned int,unsigned int,int) ; 
 scalar_t__ Dbl_isnotzero_exponentmantissa (unsigned int,unsigned int) ; 
 scalar_t__ Dbl_isnotzero_mantissa (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  Dbl_isone_roundbit (unsigned int,unsigned int,int) ; 
 scalar_t__ Dbl_isone_sign (unsigned int) ; 
 int /*<<< orphan*/  Dbl_isone_stickybit (unsigned int,unsigned int,int) ; 
 scalar_t__ Dbl_iszero_sign (unsigned int) ; 
 int /*<<< orphan*/  Dint_copytoptr (int,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Dint_decrement (int,unsigned int) ; 
 int /*<<< orphan*/  Dint_from_dbl_mantissa (unsigned int,unsigned int,int,int,unsigned int) ; 
 int /*<<< orphan*/  Dint_increment (int,unsigned int) ; 
 int /*<<< orphan*/  Dint_isone_lowp2 (unsigned int) ; 
 int /*<<< orphan*/  Dint_setone_sign (int,unsigned int) ; 
 int /*<<< orphan*/  Dint_setzero (int,unsigned int) ; 
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
 int /*<<< orphan*/  Set_inexactflag () ; 
 int /*<<< orphan*/  Set_invalidflag () ; 
 scalar_t__ TRUE ; 

int
dbl_to_dbl_fcnvfx(
		    dbl_floating_point *srcptr,
		    unsigned int *nullptr,
		    dbl_integer *dstptr,
		    unsigned int *status)
{
	register int src_exponent, resultp1;
	register unsigned int srcp1, srcp2, tempp1, tempp2, resultp2;
	register boolean inexact = FALSE;

	Dbl_copyfromptr(srcptr,srcp1,srcp2);
	src_exponent = Dbl_exponent(srcp1) - DBL_BIAS;

	/* 
	 * Test for overflow
	 */
	if (src_exponent > DBL_FX_MAX_EXP) {
		/* check for MININT */
		if ((src_exponent > DBL_FX_MAX_EXP + 1) || 
		Dbl_isnotzero_mantissa(srcp1,srcp2) || Dbl_iszero_sign(srcp1)) {
                        if (Dbl_iszero_sign(srcp1)) {
                              resultp1 = 0x7fffffff;
			      resultp2 = 0xffffffff;
			}
                        else {
			    resultp1 = 0x80000000; 
			    resultp2 = 0;
			}
	                if (Is_invalidtrap_enabled()) {
                            return(INVALIDEXCEPTION);
                        }
                        Set_invalidflag();
    		        Dint_copytoptr(resultp1,resultp2,dstptr);
			return(NOEXCEPTION);
		}
	}
 
	/*
	 * Generate result
	 */
	if (src_exponent >= 0) {
		tempp1 = srcp1;
		tempp2 = srcp2;
		Dbl_clear_signexponent_set_hidden(tempp1);
		Dint_from_dbl_mantissa(tempp1,tempp2,src_exponent,resultp1,
		resultp2);
		if (Dbl_isone_sign(srcp1)) {
			Dint_setone_sign(resultp1,resultp2);
		}

		/* check for inexact */
		if (Dbl_isinexact_to_fix(srcp1,srcp2,src_exponent)) {
                        inexact = TRUE;
                        /*  round result  */
                        switch (Rounding_mode()) {
                        case ROUNDPLUS:
                             if (Dbl_iszero_sign(srcp1)) {
				Dint_increment(resultp1,resultp2);
			     }
                             break;
                        case ROUNDMINUS:
                             if (Dbl_isone_sign(srcp1)) {
				Dint_decrement(resultp1,resultp2);
			     }
                             break;
                        case ROUNDNEAREST:
                             if (Dbl_isone_roundbit(srcp1,srcp2,src_exponent))
                                if (Dbl_isone_stickybit(srcp1,srcp2,src_exponent) || 
				(Dint_isone_lowp2(resultp2)))
                                   if (Dbl_iszero_sign(srcp1)) {
				      Dint_increment(resultp1,resultp2);
				   }
                                   else {
				      Dint_decrement(resultp1,resultp2);
				   }
                        } 
                }
	}
	else {
		Dint_setzero(resultp1,resultp2);

		/* check for inexact */
		if (Dbl_isnotzero_exponentmantissa(srcp1,srcp2)) {
                        inexact = TRUE;
                        /*  round result  */
                        switch (Rounding_mode()) {
                        case ROUNDPLUS:
                             if (Dbl_iszero_sign(srcp1)) {
				Dint_increment(resultp1,resultp2);
			     }
                             break;
                        case ROUNDMINUS:
                             if (Dbl_isone_sign(srcp1)) {
				Dint_decrement(resultp1,resultp2);
			     }
                             break;
                        case ROUNDNEAREST:
                             if (src_exponent == -1)
                                if (Dbl_isnotzero_mantissa(srcp1,srcp2))
                                   if (Dbl_iszero_sign(srcp1)) {
				      Dint_increment(resultp1,resultp2);
				   }
                                   else {
				      Dint_decrement(resultp1,resultp2);
				   }
			}
                }
	}
	Dint_copytoptr(resultp1,resultp2,dstptr);
        if (inexact) {
                if (Is_inexacttrap_enabled()) return(INEXACTEXCEPTION);
        	else Set_inexactflag();
        }
	return(NOEXCEPTION);
}