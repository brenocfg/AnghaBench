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
 int /*<<< orphan*/  CPU_FTR_ARCH_207S ; 
 int /*<<< orphan*/  CPU_FTR_HVMODE ; 
 int /*<<< orphan*/  SPRN_CIABR ; 
 scalar_t__ cpu_has_feature (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  plpar_set_ciabr (unsigned long) ; 

__attribute__((used)) static void write_ciabr(unsigned long ciabr)
{
	if (!cpu_has_feature(CPU_FTR_ARCH_207S))
		return;

	if (cpu_has_feature(CPU_FTR_HVMODE)) {
		mtspr(SPRN_CIABR, ciabr);
		return;
	}
	plpar_set_ciabr(ciabr);
}