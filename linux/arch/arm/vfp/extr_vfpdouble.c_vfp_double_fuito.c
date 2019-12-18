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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct vfp_double {int exponent; scalar_t__ significand; scalar_t__ sign; } ;

/* Variables and functions */
 scalar_t__ vfp_double_normaliseround (int,struct vfp_double*,scalar_t__,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ vfp_get_float (int) ; 

__attribute__((used)) static u32 vfp_double_fuito(int dd, int unused, int dm, u32 fpscr)
{
	struct vfp_double vdm;
	u32 m = vfp_get_float(dm);

	vdm.sign = 0;
	vdm.exponent = 1023 + 63 - 1;
	vdm.significand = (u64)m;

	return vfp_double_normaliseround(dd, &vdm, fpscr, 0, "fuito");
}