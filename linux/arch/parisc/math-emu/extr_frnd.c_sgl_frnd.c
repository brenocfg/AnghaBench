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
typedef  unsigned int sgl_floating_point ;
typedef  scalar_t__ boolean ;

/* Variables and functions */
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
 int SGL_BIAS ; 
 int SGL_INFINITY_EXPONENT ; 
 int SGL_P ; 
 int /*<<< orphan*/  Set_inexactflag () ; 
 int /*<<< orphan*/  Set_invalidflag () ; 
 int /*<<< orphan*/  Sgl_clear_exponent_set_hidden (unsigned int) ; 
 int Sgl_exponent (unsigned int) ; 
 int /*<<< orphan*/  Sgl_increment (unsigned int) ; 
 scalar_t__ Sgl_isinexact_to_fix (unsigned int,int) ; 
 scalar_t__ Sgl_isnotzero_exponentmantissa (unsigned int) ; 
 int /*<<< orphan*/  Sgl_isnotzero_mantissa (unsigned int) ; 
 scalar_t__ Sgl_isone_hiddenoverflow (unsigned int) ; 
 int /*<<< orphan*/  Sgl_isone_lowmantissa (unsigned int) ; 
 int /*<<< orphan*/  Sgl_isone_roundbit (unsigned int,int) ; 
 int /*<<< orphan*/  Sgl_isone_sign (unsigned int) ; 
 scalar_t__ Sgl_isone_signaling (unsigned int) ; 
 int /*<<< orphan*/  Sgl_isone_stickybit (unsigned int,int) ; 
 int /*<<< orphan*/  Sgl_iszero_sign (unsigned int) ; 
 int /*<<< orphan*/  Sgl_leftshift (unsigned int,int) ; 
 int /*<<< orphan*/  Sgl_rightshift (unsigned int,int) ; 
 int /*<<< orphan*/  Sgl_set_exponent (unsigned int,int) ; 
 int /*<<< orphan*/  Sgl_set_quiet (unsigned int) ; 
 int /*<<< orphan*/  Sgl_setzero_exponentmantissa (unsigned int) ; 
 scalar_t__ TRUE ; 

int
sgl_frnd(sgl_floating_point *srcptr,
	unsigned int *nullptr,
	sgl_floating_point *dstptr,
	unsigned int *status)
{
	register unsigned int src, result;
	register int src_exponent;
	register boolean inexact = FALSE;

	src = *srcptr;
        /*
         * check source operand for NaN or infinity
         */
        if ((src_exponent = Sgl_exponent(src)) == SGL_INFINITY_EXPONENT) {
                /*
                 * is signaling NaN?
                 */
                if (Sgl_isone_signaling(src)) {
                        /* trap if INVALIDTRAP enabled */
                        if (Is_invalidtrap_enabled()) return(INVALIDEXCEPTION);
                        /* make NaN quiet */
                        Set_invalidflag();
                        Sgl_set_quiet(src);
                }
                /*
                 * return quiet NaN or infinity
                 */
                *dstptr = src;
                return(NOEXCEPTION);
        }
	/* 
	 * Need to round?
	 */
	if ((src_exponent -= SGL_BIAS) >= SGL_P - 1) {
		*dstptr = src;
		return(NOEXCEPTION);
	}
	/*
	 * Generate result
	 */
	if (src_exponent >= 0) {
		Sgl_clear_exponent_set_hidden(src);
		result = src;
		Sgl_rightshift(result,(SGL_P-1) - (src_exponent));
		/* check for inexact */
		if (Sgl_isinexact_to_fix(src,src_exponent)) {
			inexact = TRUE;
			/*  round result  */
			switch (Rounding_mode()) {
			case ROUNDPLUS:
			     if (Sgl_iszero_sign(src)) Sgl_increment(result);
			     break;
			case ROUNDMINUS:
			     if (Sgl_isone_sign(src)) Sgl_increment(result);
			     break;
			case ROUNDNEAREST:
			     if (Sgl_isone_roundbit(src,src_exponent))
			        if (Sgl_isone_stickybit(src,src_exponent) 
				|| (Sgl_isone_lowmantissa(result))) 
					Sgl_increment(result);
			} 
		}
		Sgl_leftshift(result,(SGL_P-1) - (src_exponent));
		if (Sgl_isone_hiddenoverflow(result)) 
			Sgl_set_exponent(result,src_exponent + (SGL_BIAS+1));
		else Sgl_set_exponent(result,src_exponent + SGL_BIAS);
	}
	else {
		result = src;  		/* set sign */
		Sgl_setzero_exponentmantissa(result);
		/* check for inexact */
		if (Sgl_isnotzero_exponentmantissa(src)) {
			inexact = TRUE;
			/*  round result  */
			switch (Rounding_mode()) {
			case ROUNDPLUS:
			     if (Sgl_iszero_sign(src)) 
				Sgl_set_exponent(result,SGL_BIAS);
			     break;
			case ROUNDMINUS:
			     if (Sgl_isone_sign(src)) 
				Sgl_set_exponent(result,SGL_BIAS);
			     break;
			case ROUNDNEAREST:
			     if (src_exponent == -1)
			        if (Sgl_isnotzero_mantissa(src))
				   Sgl_set_exponent(result,SGL_BIAS);
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