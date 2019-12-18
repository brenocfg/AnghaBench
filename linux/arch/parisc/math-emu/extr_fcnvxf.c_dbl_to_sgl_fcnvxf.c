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
typedef  int /*<<< orphan*/  dbl_integer ;

/* Variables and functions */
 int /*<<< orphan*/  Dint_copyfromptr (int /*<<< orphan*/ *,int,unsigned int) ; 
 scalar_t__ Dint_isinexact_to_sgl (int,unsigned int) ; 
 int /*<<< orphan*/  Dint_negate (int,unsigned int) ; 
 int /*<<< orphan*/  Find_ms_one_bit (int,int) ; 
 int INEXACTEXCEPTION ; 
 scalar_t__ Is_inexacttrap_enabled () ; 
 int NOEXCEPTION ; 
#define  ROUNDMINUS 130 
#define  ROUNDNEAREST 129 
#define  ROUNDPLUS 128 
 int Rounding_mode () ; 
 scalar_t__ SGL_BIAS ; 
 int SGL_EXP_LENGTH ; 
 int /*<<< orphan*/  Set_inexactflag () ; 
 int /*<<< orphan*/  Sgl_increment (unsigned int) ; 
 int /*<<< orphan*/  Sgl_isone_sign (unsigned int) ; 
 int /*<<< orphan*/  Sgl_iszero_sign (unsigned int) ; 
 int /*<<< orphan*/  Sgl_roundnearest_from_dint (int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  Sgl_set_exponent (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  Sgl_set_mantissa (unsigned int,int) ; 
 int /*<<< orphan*/  Sgl_setone_sign (unsigned int) ; 
 int /*<<< orphan*/  Sgl_setzero (unsigned int) ; 
 int /*<<< orphan*/  Sgl_setzero_sign (unsigned int) ; 
 int /*<<< orphan*/  Variable_shift_double (int,unsigned int,int,int) ; 

int
dbl_to_sgl_fcnvxf(
			dbl_integer *srcptr,
			unsigned int *nullptr,
			sgl_floating_point *dstptr,
			unsigned int *status)
{
	int dst_exponent, srcp1;
	unsigned int result = 0, srcp2;

	Dint_copyfromptr(srcptr,srcp1,srcp2);
	/* 
	 * set sign bit of result and get magnitude of source 
	 */
	if (srcp1 < 0) {
		Sgl_setone_sign(result);  
		Dint_negate(srcp1,srcp2);
	}
	else {
		Sgl_setzero_sign(result);
        	/* Check for zero */
        	if (srcp1 == 0 && srcp2 == 0) {
                	Sgl_setzero(result);
                	*dstptr = result;
                	return(NOEXCEPTION);
		}
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
		/*  left justify source, with msb at bit position 1  */
		if (dst_exponent >= 0) {
			srcp1 = srcp2 << dst_exponent;    
			srcp2 = 0;
		}
		else {
			srcp1 = srcp2 >> 1;
			srcp2 <<= 31; 
		}
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
		/*  left justify source, with msb at bit position 1  */
		if (dst_exponent > 0) {
			Variable_shift_double(srcp1,srcp2,(32-dst_exponent),
			 srcp1); 
			srcp2 <<= dst_exponent;
		}
		/*
		 * If dst_exponent = 0, we don't need to shift anything.
		 * If dst_exponent = -1, src = - 2**63 so we won't need to 
		 * shift srcp2.
		 */
		else srcp1 >>= -(dst_exponent);
	}
	Sgl_set_mantissa(result, srcp1 >> SGL_EXP_LENGTH - 1);
	Sgl_set_exponent(result, (62+SGL_BIAS) - dst_exponent);

	/* check for inexact */
	if (Dint_isinexact_to_sgl(srcp1,srcp2)) {
		switch (Rounding_mode()) {
			case ROUNDPLUS: 
				if (Sgl_iszero_sign(result)) 
					Sgl_increment(result);
				break;
			case ROUNDMINUS: 
				if (Sgl_isone_sign(result)) 
					Sgl_increment(result);
				break;
			case ROUNDNEAREST:
				Sgl_roundnearest_from_dint(srcp1,srcp2,result);
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