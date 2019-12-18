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
 int /*<<< orphan*/  Find_ms_one_bit (unsigned int,int) ; 
 int INEXACTEXCEPTION ; 
 scalar_t__ Is_inexacttrap_enabled () ; 
 int NOEXCEPTION ; 
#define  ROUNDMINUS 130 
#define  ROUNDNEAREST 129 
#define  ROUNDPLUS 128 
 int Rounding_mode () ; 
 scalar_t__ SGL_BIAS ; 
 unsigned int SGL_EXP_LENGTH ; 
 int /*<<< orphan*/  Set_inexactflag () ; 
 int /*<<< orphan*/  Sgl_increment (unsigned int) ; 
 int /*<<< orphan*/  Sgl_roundnearest_from_suint (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  Sgl_set_exponent (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  Sgl_set_mantissa (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  Sgl_setzero (unsigned int) ; 
 scalar_t__ Suint_isinexact_to_sgl (unsigned int) ; 

int
sgl_to_sgl_fcnvuf(
			unsigned int *srcptr,
			unsigned int *nullptr,
			sgl_floating_point *dstptr,
			unsigned int *status)
{
	register unsigned int src, result = 0;
	register int dst_exponent;

	src = *srcptr;

	/* Check for zero */ 
	if (src == 0) { 
	       	Sgl_setzero(result); 
		*dstptr = result;
	       	return(NOEXCEPTION); 
	} 
	/*
	 * Generate exponent and normalized mantissa
	 */
	dst_exponent = 16;    /* initialize for normalization */
	/*
	 * Check word for most significant bit set.  Returns
	 * a value in dst_exponent indicating the bit position,
	 * between -1 and 30.
	 */
	Find_ms_one_bit(src,dst_exponent);
	/*  left justify source, with msb at bit position 0  */
	src <<= dst_exponent+1;
	Sgl_set_mantissa(result, src >> SGL_EXP_LENGTH);
	Sgl_set_exponent(result, 30+SGL_BIAS - dst_exponent);

	/* check for inexact */
	if (Suint_isinexact_to_sgl(src)) {
		switch (Rounding_mode()) {
			case ROUNDPLUS: 
				Sgl_increment(result);
				break;
			case ROUNDMINUS: /* never negative */
				break;
			case ROUNDNEAREST:
				Sgl_roundnearest_from_suint(src,result);
				break;
		}
		if (Is_inexacttrap_enabled()) {
			*dstptr = result;
			return(INEXACTEXCEPTION);
		}
		else Set_inexactflag();
	}
	*dstptr = result;
	return(NOEXCEPTION);
}