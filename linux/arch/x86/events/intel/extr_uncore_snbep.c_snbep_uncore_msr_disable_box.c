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
typedef  int /*<<< orphan*/  u64 ;
struct intel_uncore_box {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNBEP_PMON_BOX_CTL_FRZ ; 
 int /*<<< orphan*/  rdmsrl (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int uncore_msr_box_ctl (struct intel_uncore_box*) ; 
 int /*<<< orphan*/  wrmsrl (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snbep_uncore_msr_disable_box(struct intel_uncore_box *box)
{
	u64 config;
	unsigned msr;

	msr = uncore_msr_box_ctl(box);
	if (msr) {
		rdmsrl(msr, config);
		config |= SNBEP_PMON_BOX_CTL_FRZ;
		wrmsrl(msr, config);
	}
}