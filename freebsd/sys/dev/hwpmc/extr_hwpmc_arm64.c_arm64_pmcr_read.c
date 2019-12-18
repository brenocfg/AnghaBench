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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  READ_SPECIALREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmcr_el0 ; 

__attribute__((used)) static uint32_t
arm64_pmcr_read(void)
{
	uint32_t reg;

	reg = READ_SPECIALREG(pmcr_el0);

	return (reg);
}