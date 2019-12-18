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

/* Variables and functions */
 scalar_t__ DBL_BIAS ; 
 int DBL_EXP_LENGTH ; 
 int /*<<< orphan*/  Dbl_copytoptr (unsigned int,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Dbl_set_exponent (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  Dbl_set_mantissap1 (unsigned int,int) ; 
 int /*<<< orphan*/  Dbl_set_mantissap2 (unsigned int,int) ; 
 int /*<<< orphan*/  Dbl_setone_sign (unsigned int) ; 
 int /*<<< orphan*/  Dbl_setzero (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  Dbl_setzero_sign (unsigned int) ; 
 int /*<<< orphan*/  Find_ms_one_bit (int,int) ; 
 int /*<<< orphan*/  Int_negate (int) ; 
 int NOEXCEPTION ; 

int
sgl_to_dbl_fcnvxf(
		    int *srcptr,
		    unsigned int *nullptr,
		    dbl_floating_point *dstptr,
		    unsigned int *status)
{
	register int src, dst_exponent;
	register unsigned int resultp1 = 0, resultp2 = 0;

	src = *srcptr;
	/* 
	 * set sign bit of result and get magnitude of source 
	 */
	if (src < 0) {
		Dbl_setone_sign(resultp1);  
		Int_negate(src);
	}
	else {
		Dbl_setzero_sign(resultp1);
        	/* Check for zero */
        	if (src == 0) {
                	Dbl_setzero(resultp1,resultp2);
                	Dbl_copytoptr(resultp1,resultp2,dstptr);
                	return(NOEXCEPTION);
        	}
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
	/*  left justify source, with msb at bit position 1  */
	if (dst_exponent >= 0) src <<= dst_exponent;
	else src = 1 << 30;
	Dbl_set_mantissap1(resultp1, src >> DBL_EXP_LENGTH - 1);
	Dbl_set_mantissap2(resultp2, src << (33-DBL_EXP_LENGTH));
	Dbl_set_exponent(resultp1, (30+DBL_BIAS) - dst_exponent);
	Dbl_copytoptr(resultp1,resultp2,dstptr);
	return(NOEXCEPTION);
}