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
typedef  int u32 ;
typedef  int s32 ;

/* Variables and functions */
 int FPSCR_C ; 
 int FPSCR_IOC ; 
 int FPSCR_N ; 
 int FPSCR_V ; 
 int FPSCR_Z ; 
 int VFP_SINGLE_MANTISSA_BITS ; 
 int vfp_get_float (int) ; 
 scalar_t__ vfp_single_packed_abs (int) ; 
 int vfp_single_packed_exponent (int) ; 
 int vfp_single_packed_mantissa (int) ; 
 scalar_t__ vfp_single_packed_sign (int) ; 

__attribute__((used)) static u32 vfp_compare(int sd, int signal_on_qnan, s32 m, u32 fpscr)
{
	s32 d;
	u32 ret = 0;

	d = vfp_get_float(sd);
	if (vfp_single_packed_exponent(m) == 255 && vfp_single_packed_mantissa(m)) {
		ret |= FPSCR_C | FPSCR_V;
		if (signal_on_qnan || !(vfp_single_packed_mantissa(m) & (1 << (VFP_SINGLE_MANTISSA_BITS - 1))))
			/*
			 * Signalling NaN, or signalling on quiet NaN
			 */
			ret |= FPSCR_IOC;
	}

	if (vfp_single_packed_exponent(d) == 255 && vfp_single_packed_mantissa(d)) {
		ret |= FPSCR_C | FPSCR_V;
		if (signal_on_qnan || !(vfp_single_packed_mantissa(d) & (1 << (VFP_SINGLE_MANTISSA_BITS - 1))))
			/*
			 * Signalling NaN, or signalling on quiet NaN
			 */
			ret |= FPSCR_IOC;
	}

	if (ret == 0) {
		if (d == m || vfp_single_packed_abs(d | m) == 0) {
			/*
			 * equal
			 */
			ret |= FPSCR_Z | FPSCR_C;
		} else if (vfp_single_packed_sign(d ^ m)) {
			/*
			 * different signs
			 */
			if (vfp_single_packed_sign(d))
				/*
				 * d is negative, so d < m
				 */
				ret |= FPSCR_N;
			else
				/*
				 * d is positive, so d > m
				 */
				ret |= FPSCR_C;
		} else if ((vfp_single_packed_sign(d) != 0) ^ (d < m)) {
			/*
			 * d < m
			 */
			ret |= FPSCR_N;
		} else if ((vfp_single_packed_sign(d) != 0) ^ (d > m)) {
			/*
			 * d > m
			 */
			ret |= FPSCR_C;
		}
	}
	return ret;
}