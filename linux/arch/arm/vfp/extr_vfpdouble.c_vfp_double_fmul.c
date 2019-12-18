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
struct vfp_double {scalar_t__ exponent; scalar_t__ significand; } ;

/* Variables and functions */
 int /*<<< orphan*/  vfp_double_multiply (struct vfp_double*,struct vfp_double*,struct vfp_double*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfp_double_normalise_denormal (struct vfp_double*) ; 
 int /*<<< orphan*/  vfp_double_normaliseround (int,struct vfp_double*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  vfp_double_unpack (struct vfp_double*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfp_get_double (int) ; 

__attribute__((used)) static u32 vfp_double_fmul(int dd, int dn, int dm, u32 fpscr)
{
	struct vfp_double vdd, vdn, vdm;
	u32 exceptions;

	vfp_double_unpack(&vdn, vfp_get_double(dn));
	if (vdn.exponent == 0 && vdn.significand)
		vfp_double_normalise_denormal(&vdn);

	vfp_double_unpack(&vdm, vfp_get_double(dm));
	if (vdm.exponent == 0 && vdm.significand)
		vfp_double_normalise_denormal(&vdm);

	exceptions = vfp_double_multiply(&vdd, &vdn, &vdm, fpscr);
	return vfp_double_normaliseround(dd, &vdd, fpscr, exceptions, "fmul");
}