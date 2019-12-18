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
typedef  int quad_t ;

/* Variables and functions */
 int P5FLAG_E ; 
 int P5FLAG_OS ; 
 int P5FLAG_USR ; 
 int PMCF_E ; 
 int PMCF_EN ; 
 int PMCF_OS ; 
 int PMCF_USR ; 
 int* ctl_shadow ; 
 int /*<<< orphan*/ * msr_ctl ; 
 int /*<<< orphan*/  wrmsr (int /*<<< orphan*/ ,int) ; 

int
writectl5(int pmc)
{
	quad_t newval = 0;

	if (ctl_shadow[1] & (PMCF_EN << 16)) {
		if (ctl_shadow[1] & (PMCF_USR << 16))
			newval |= P5FLAG_USR << 16;
		if (ctl_shadow[1] & (PMCF_OS << 16))
			newval |= P5FLAG_OS << 16;
		if (!(ctl_shadow[1] & (PMCF_E << 16)))
			newval |= P5FLAG_E << 16;
		newval |= (ctl_shadow[1] & 0x3f) << 16;
	}
	if (ctl_shadow[0] & (PMCF_EN << 16)) {
		if (ctl_shadow[0] & (PMCF_USR << 16))
			newval |= P5FLAG_USR;
		if (ctl_shadow[0] & (PMCF_OS << 16))
			newval |= P5FLAG_OS;
		if (!(ctl_shadow[0] & (PMCF_E << 16)))
			newval |= P5FLAG_E;
		newval |= ctl_shadow[0] & 0x3f;
	}

	wrmsr(msr_ctl[0], newval);
	return 0;		/* XXX should check for unimplemented bits */
}