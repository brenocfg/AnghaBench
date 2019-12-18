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
struct mtrr_var_range {int /*<<< orphan*/  mask_hi; int /*<<< orphan*/  mask_lo; int /*<<< orphan*/  base_hi; int /*<<< orphan*/  base_lo; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTRRphysBase_MSR (unsigned int) ; 
 int /*<<< orphan*/  MTRRphysMask_MSR (unsigned int) ; 
 int /*<<< orphan*/  rdmsr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
get_mtrr_var_range(unsigned int index, struct mtrr_var_range *vr)
{
	rdmsr(MTRRphysBase_MSR(index), vr->base_lo, vr->base_hi);
	rdmsr(MTRRphysMask_MSR(index), vr->mask_lo, vr->mask_hi);
}