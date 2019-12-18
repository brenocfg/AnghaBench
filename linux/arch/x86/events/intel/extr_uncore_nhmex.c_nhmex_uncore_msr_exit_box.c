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
 int /*<<< orphan*/  NHMEX_U_MSR_PMON_GLOBAL_CTL ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nhmex_uncore_msr_exit_box(struct intel_uncore_box *box)
{
	wrmsrl(NHMEX_U_MSR_PMON_GLOBAL_CTL, 0);
}