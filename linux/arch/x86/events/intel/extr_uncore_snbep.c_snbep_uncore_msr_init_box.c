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
struct intel_uncore_box {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNBEP_PMON_BOX_CTL_INT ; 
 unsigned int uncore_msr_box_ctl (struct intel_uncore_box*) ; 
 int /*<<< orphan*/  wrmsrl (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snbep_uncore_msr_init_box(struct intel_uncore_box *box)
{
	unsigned msr = uncore_msr_box_ctl(box);

	if (msr)
		wrmsrl(msr, SNBEP_PMON_BOX_CTL_INT);
}