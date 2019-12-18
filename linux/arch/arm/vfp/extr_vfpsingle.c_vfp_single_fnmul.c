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
struct vfp_single {scalar_t__ exponent; int /*<<< orphan*/  sign; scalar_t__ significand; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfp_get_float (int) ; 
 int /*<<< orphan*/  vfp_sign_negate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfp_single_multiply (struct vfp_single*,struct vfp_single*,struct vfp_single*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfp_single_normalise_denormal (struct vfp_single*) ; 
 int /*<<< orphan*/  vfp_single_normaliseround (int,struct vfp_single*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  vfp_single_unpack (struct vfp_single*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 vfp_single_fnmul(int sd, int sn, s32 m, u32 fpscr)
{
	struct vfp_single vsd, vsn, vsm;
	u32 exceptions;
	s32 n = vfp_get_float(sn);

	pr_debug("VFP: s%u = %08x\n", sn, n);

	vfp_single_unpack(&vsn, n);
	if (vsn.exponent == 0 && vsn.significand)
		vfp_single_normalise_denormal(&vsn);

	vfp_single_unpack(&vsm, m);
	if (vsm.exponent == 0 && vsm.significand)
		vfp_single_normalise_denormal(&vsm);

	exceptions = vfp_single_multiply(&vsd, &vsn, &vsm, fpscr);
	vsd.sign = vfp_sign_negate(vsd.sign);
	return vfp_single_normaliseround(sd, &vsd, fpscr, exceptions, "fnmul");
}