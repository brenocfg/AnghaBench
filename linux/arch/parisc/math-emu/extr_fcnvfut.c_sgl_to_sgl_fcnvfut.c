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

/* Variables and functions */
 int INEXACTEXCEPTION ; 
 int INVALIDEXCEPTION ; 
 scalar_t__ Is_inexacttrap_enabled () ; 
 scalar_t__ Is_invalidtrap_enabled () ; 
 int NOEXCEPTION ; 
 int SGL_BIAS ; 
 int SGL_FX_MAX_EXP ; 
 int /*<<< orphan*/  Set_inexactflag () ; 
 int /*<<< orphan*/  Set_invalidflag () ; 
 int /*<<< orphan*/  Sgl_clear_signexponent_set_hidden (unsigned int) ; 
 int Sgl_exponent (unsigned int) ; 
 scalar_t__ Sgl_isinexact_to_unsigned (unsigned int,int) ; 
 scalar_t__ Sgl_isnotzero_exponentmantissa (unsigned int) ; 
 scalar_t__ Sgl_isone_sign (unsigned int) ; 
 int /*<<< orphan*/  Suint_from_sgl_mantissa (unsigned int,int,unsigned int) ; 

int
sgl_to_sgl_fcnvfut (sgl_floating_point * srcptr, unsigned int *nullptr,
		    unsigned int *dstptr, unsigned int *status)
{
	register unsigned int src, result;
	register int src_exponent;

	src = *srcptr;
	src_exponent = Sgl_exponent(src) - SGL_BIAS;

	/* 
	 * Test for overflow
	 */
	if (src_exponent > SGL_FX_MAX_EXP + 1) {
		if (Sgl_isone_sign(src)) {
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
		if (Sgl_isone_sign(src)) {
			result = 0;
			if (Is_invalidtrap_enabled()) {
				return(INVALIDEXCEPTION);
			}
			Set_invalidflag();
			*dstptr = result;
			return(NOEXCEPTION);
		}
		Sgl_clear_signexponent_set_hidden(src);
		Suint_from_sgl_mantissa(src,src_exponent,result);
		*dstptr = result;

		/* check for inexact */
		if (Sgl_isinexact_to_unsigned(src,src_exponent)) {
			if (Is_inexacttrap_enabled()) return(INEXACTEXCEPTION);
			else Set_inexactflag();
		}
	}
	else {
		*dstptr = 0;

		/* check for inexact */
		if (Sgl_isnotzero_exponentmantissa(src)) {
			if (Is_inexacttrap_enabled()) return(INEXACTEXCEPTION);
			else Set_inexactflag();
		}
	}
	return(NOEXCEPTION);
}