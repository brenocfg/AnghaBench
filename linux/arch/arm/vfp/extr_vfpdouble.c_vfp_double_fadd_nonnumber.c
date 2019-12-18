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
struct vfp_double {int sign; } ;

/* Variables and functions */
 int /*<<< orphan*/  FPSCR_IOC ; 
 int VFP_INFINITY ; 
 int VFP_NUMBER ; 
 struct vfp_double vfp_double_default_qnan ; 
 int vfp_double_type (struct vfp_double*) ; 
 int /*<<< orphan*/  vfp_propagate_nan (struct vfp_double*,struct vfp_double*,struct vfp_double*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32
vfp_double_fadd_nonnumber(struct vfp_double *vdd, struct vfp_double *vdn,
			  struct vfp_double *vdm, u32 fpscr)
{
	struct vfp_double *vdp;
	u32 exceptions = 0;
	int tn, tm;

	tn = vfp_double_type(vdn);
	tm = vfp_double_type(vdm);

	if (tn & tm & VFP_INFINITY) {
		/*
		 * Two infinities.  Are they different signs?
		 */
		if (vdn->sign ^ vdm->sign) {
			/*
			 * different signs -> invalid
			 */
			exceptions = FPSCR_IOC;
			vdp = &vfp_double_default_qnan;
		} else {
			/*
			 * same signs -> valid
			 */
			vdp = vdn;
		}
	} else if (tn & VFP_INFINITY && tm & VFP_NUMBER) {
		/*
		 * One infinity and one number -> infinity
		 */
		vdp = vdn;
	} else {
		/*
		 * 'n' is a NaN of some type
		 */
		return vfp_propagate_nan(vdd, vdn, vdm, fpscr);
	}
	*vdd = *vdp;
	return exceptions;
}