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
struct vfp_single {int significand; int exponent; } ;

/* Variables and functions */
 int fls (int) ; 
 int /*<<< orphan*/  vfp_single_dump (char*,struct vfp_single*) ; 

__attribute__((used)) static void vfp_single_normalise_denormal(struct vfp_single *vs)
{
	int bits = 31 - fls(vs->significand);

	vfp_single_dump("normalise_denormal: in", vs);

	if (bits) {
		vs->exponent -= bits - 1;
		vs->significand <<= bits;
	}

	vfp_single_dump("normalise_denormal: out", vs);
}