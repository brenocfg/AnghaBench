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

/* Variables and functions */
 int /*<<< orphan*/  pebs_ucodes ; 
 int /*<<< orphan*/  x86_cpu_has_min_microcode_rev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool intel_snb_pebs_broken(void)
{
	return !x86_cpu_has_min_microcode_rev(pebs_ucodes);
}