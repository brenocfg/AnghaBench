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
typedef  int u64 ;
typedef  int u32 ;
struct vfp_single {scalar_t__ sign; int exponent; int significand; } ;
typedef  int s64 ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int FPSCR_IOC ; 
 int VFP_DENORMAL ; 
 int VFP_INFINITY ; 
 int VFP_NAN ; 
 int VFP_SINGLE_LOW_BITS_MASK ; 
 int VFP_ZERO ; 
 int /*<<< orphan*/  pr_debug (char*,int,int) ; 
 int vfp_estimate_sqrt_significand (int,int) ; 
 int vfp_propagate_nan (struct vfp_single*,struct vfp_single*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vfp_put_float (int /*<<< orphan*/ ,int) ; 
 int vfp_shiftright32jamming (int,int) ; 
 struct vfp_single vfp_single_default_qnan ; 
 int /*<<< orphan*/  vfp_single_dump (char*,struct vfp_single*) ; 
 int /*<<< orphan*/  vfp_single_normalise_denormal (struct vfp_single*) ; 
 int vfp_single_normaliseround (int,struct vfp_single*,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  vfp_single_pack (struct vfp_single*) ; 
 int vfp_single_type (struct vfp_single*) ; 
 int /*<<< orphan*/  vfp_single_unpack (struct vfp_single*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 vfp_single_fsqrt(int sd, int unused, s32 m, u32 fpscr)
{
	struct vfp_single vsm, vsd;
	int ret, tm;

	vfp_single_unpack(&vsm, m);
	tm = vfp_single_type(&vsm);
	if (tm & (VFP_NAN|VFP_INFINITY)) {
		struct vfp_single *vsp = &vsd;

		if (tm & VFP_NAN)
			ret = vfp_propagate_nan(vsp, &vsm, NULL, fpscr);
		else if (vsm.sign == 0) {
 sqrt_copy:
			vsp = &vsm;
			ret = 0;
		} else {
 sqrt_invalid:
			vsp = &vfp_single_default_qnan;
			ret = FPSCR_IOC;
		}
		vfp_put_float(vfp_single_pack(vsp), sd);
		return ret;
	}

	/*
	 * sqrt(+/- 0) == +/- 0
	 */
	if (tm & VFP_ZERO)
		goto sqrt_copy;

	/*
	 * Normalise a denormalised number
	 */
	if (tm & VFP_DENORMAL)
		vfp_single_normalise_denormal(&vsm);

	/*
	 * sqrt(<0) = invalid
	 */
	if (vsm.sign)
		goto sqrt_invalid;

	vfp_single_dump("sqrt", &vsm);

	/*
	 * Estimate the square root.
	 */
	vsd.sign = 0;
	vsd.exponent = ((vsm.exponent - 127) >> 1) + 127;
	vsd.significand = vfp_estimate_sqrt_significand(vsm.exponent, vsm.significand) + 2;

	vfp_single_dump("sqrt estimate", &vsd);

	/*
	 * And now adjust.
	 */
	if ((vsd.significand & VFP_SINGLE_LOW_BITS_MASK) <= 5) {
		if (vsd.significand < 2) {
			vsd.significand = 0xffffffff;
		} else {
			u64 term;
			s64 rem;
			vsm.significand <<= !(vsm.exponent & 1);
			term = (u64)vsd.significand * vsd.significand;
			rem = ((u64)vsm.significand << 32) - term;

			pr_debug("VFP: term=%016llx rem=%016llx\n", term, rem);

			while (rem < 0) {
				vsd.significand -= 1;
				rem += ((u64)vsd.significand << 1) | 1;
			}
			vsd.significand |= rem != 0;
		}
	}
	vsd.significand = vfp_shiftright32jamming(vsd.significand, 1);

	return vfp_single_normaliseround(sd, &vsd, fpscr, 0, "fsqrt");
}