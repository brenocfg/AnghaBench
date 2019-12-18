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
typedef  int /*<<< orphan*/  dbl_unsigned ;

/* Variables and functions */
 int /*<<< orphan*/  Duint_copyfromptr (int /*<<< orphan*/ *,unsigned int,unsigned int) ; 
 scalar_t__ Duint_isinexact_to_sgl (unsigned int,unsigned int) ; 
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
 int /*<<< orphan*/  Sgl_roundnearest_from_duint (unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  Sgl_set_exponent (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  Sgl_set_mantissa (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  Sgl_setzero (unsigned int) ; 
 int /*<<< orphan*/  Variable_shift_double (unsigned int,unsigned int,int,unsigned int) ; 

int
dbl_to_sgl_fcnvuf(
			dbl_unsigned *srcptr,
			unsigned int *nullptr,
			sgl_floating_point *dstptr,
			unsigned int *status)
{
	int dst_exponent;
	unsigned int srcp1, srcp2, result = 0;

	Duint_copyfromptr(srcptr,srcp1,srcp2);

	/* Check for zero */
	if (srcp1 == 0 && srcp2 == 0) {
	       	Sgl_setzero(result);
	       	*dstptr = result;
	       	return(NOEXCEPTION);
	}
	/*
	 * Generate exponent and normalized mantissa
	 */
	dst_exponent = 16;    /* initialize for normalization */
	if (srcp1 == 0) {
		/*
		 * Check word for most significant bit set.  Returns
		 * a value in dst_exponent indicating the bit position,
		 * between -1 and 30.
		 */
		Find_ms_one_bit(srcp2,dst_exponent);
		/*  left justify source, with msb at bit position 0  */
		srcp1 = srcp2 << dst_exponent+1;    
		srcp2 = 0;
		/*
		 *  since msb set is in second word, need to 
		 *  adjust bit position count
		 */
		dst_exponent += 32;
	}
	else {
		/*
		 * Check word for most significant bit set.  Returns
		 * a value in dst_exponent indicating the bit position,
		 * between -1 and 30.
		 *
		 */
		Find_ms_one_bit(srcp1,dst_exponent);
		/*  left justify source, with msb at bit position 0  */
		if (dst_exponent >= 0) {
			Variable_shift_double(srcp1,srcp2,(31-dst_exponent),
			 srcp1); 
			srcp2 <<= dst_exponent+1;
		}
	}
	Sgl_set_mantissa(result, srcp1 >> SGL_EXP_LENGTH);
	Sgl_set_exponent(result, (62+SGL_BIAS) - dst_exponent);

	/* check for inexact */
	if (Duint_isinexact_to_sgl(srcp1,srcp2)) {
		switch (Rounding_mode()) {
			case ROUNDPLUS: 
				Sgl_increment(result);
				break;
			case ROUNDMINUS: /* never negative */
				break;
			case ROUNDNEAREST:
				Sgl_roundnearest_from_duint(srcp1,srcp2,result);
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