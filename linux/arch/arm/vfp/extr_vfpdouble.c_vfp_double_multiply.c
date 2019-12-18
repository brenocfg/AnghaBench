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
typedef  int /*<<< orphan*/  u32 ;
struct vfp_double {int exponent; int sign; int significand; } ;

/* Variables and functions */
 int /*<<< orphan*/  FPSCR_IOC ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 struct vfp_double vfp_double_default_qnan ; 
 int /*<<< orphan*/  vfp_double_dump (char*,struct vfp_double*) ; 
 int vfp_hi64multiply64 (int,int) ; 
 int /*<<< orphan*/  vfp_propagate_nan (struct vfp_double*,struct vfp_double*,struct vfp_double*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32
vfp_double_multiply(struct vfp_double *vdd, struct vfp_double *vdn,
		    struct vfp_double *vdm, u32 fpscr)
{
	vfp_double_dump("VDN", vdn);
	vfp_double_dump("VDM", vdm);

	/*
	 * Ensure that 'n' is the largest magnitude number.  Note that
	 * if 'n' and 'm' have equal exponents, we do not swap them.
	 * This ensures that NaN propagation works correctly.
	 */
	if (vdn->exponent < vdm->exponent) {
		struct vfp_double *t = vdn;
		vdn = vdm;
		vdm = t;
		pr_debug("VFP: swapping M <-> N\n");
	}

	vdd->sign = vdn->sign ^ vdm->sign;

	/*
	 * If 'n' is an infinity or NaN, handle it.  'm' may be anything.
	 */
	if (vdn->exponent == 2047) {
		if (vdn->significand || (vdm->exponent == 2047 && vdm->significand))
			return vfp_propagate_nan(vdd, vdn, vdm, fpscr);
		if ((vdm->exponent | vdm->significand) == 0) {
			*vdd = vfp_double_default_qnan;
			return FPSCR_IOC;
		}
		vdd->exponent = vdn->exponent;
		vdd->significand = 0;
		return 0;
	}

	/*
	 * If 'm' is zero, the result is always zero.  In this case,
	 * 'n' may be zero or a number, but it doesn't matter which.
	 */
	if ((vdm->exponent | vdm->significand) == 0) {
		vdd->exponent = 0;
		vdd->significand = 0;
		return 0;
	}

	/*
	 * We add 2 to the destination exponent for the same reason
	 * as the addition case - though this time we have +1 from
	 * each input operand.
	 */
	vdd->exponent = vdn->exponent + vdm->exponent - 1023 + 2;
	vdd->significand = vfp_hi64multiply64(vdn->significand, vdm->significand);

	vfp_double_dump("VDD", vdd);
	return 0;
}