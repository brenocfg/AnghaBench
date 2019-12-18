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
struct vfp_double {int significand; int exponent; } ;

/* Variables and functions */
 int fls (int) ; 
 int /*<<< orphan*/  vfp_double_dump (char*,struct vfp_double*) ; 

__attribute__((used)) static void vfp_double_normalise_denormal(struct vfp_double *vd)
{
	int bits = 31 - fls(vd->significand >> 32);
	if (bits == 31)
		bits = 63 - fls(vd->significand);

	vfp_double_dump("normalise_denormal: in", vd);

	if (bits) {
		vd->exponent -= bits - 1;
		vd->significand <<= bits;
	}

	vfp_double_dump("normalise_denormal: out", vd);
}