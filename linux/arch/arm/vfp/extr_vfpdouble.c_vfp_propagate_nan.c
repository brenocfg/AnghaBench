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
struct vfp_double {int /*<<< orphan*/  significand; } ;

/* Variables and functions */
 int FPSCR_DEFAULT_NAN ; 
 int FPSCR_IOC ; 
 int /*<<< orphan*/  VFP_DOUBLE_SIGNIFICAND_QNAN ; 
 int VFP_NAN_FLAG ; 
 int VFP_QNAN ; 
 int VFP_SNAN ; 
 struct vfp_double vfp_double_default_qnan ; 
 int vfp_double_type (struct vfp_double*) ; 

__attribute__((used)) static u32
vfp_propagate_nan(struct vfp_double *vdd, struct vfp_double *vdn,
		  struct vfp_double *vdm, u32 fpscr)
{
	struct vfp_double *nan;
	int tn, tm = 0;

	tn = vfp_double_type(vdn);

	if (vdm)
		tm = vfp_double_type(vdm);

	if (fpscr & FPSCR_DEFAULT_NAN)
		/*
		 * Default NaN mode - always returns a quiet NaN
		 */
		nan = &vfp_double_default_qnan;
	else {
		/*
		 * Contemporary mode - select the first signalling
		 * NAN, or if neither are signalling, the first
		 * quiet NAN.
		 */
		if (tn == VFP_SNAN || (tm != VFP_SNAN && tn == VFP_QNAN))
			nan = vdn;
		else
			nan = vdm;
		/*
		 * Make the NaN quiet.
		 */
		nan->significand |= VFP_DOUBLE_SIGNIFICAND_QNAN;
	}

	*vdd = *nan;

	/*
	 * If one was a signalling NAN, raise invalid operation.
	 */
	return tn == VFP_SNAN || tm == VFP_SNAN ? FPSCR_IOC : VFP_NAN_FLAG;
}