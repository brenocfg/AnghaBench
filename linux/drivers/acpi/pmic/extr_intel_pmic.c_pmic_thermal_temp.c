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
typedef  scalar_t__ u32 ;
struct intel_pmic_opregion {int dummy; } ;

/* Variables and functions */
 scalar_t__ ACPI_READ ; 
 int EINVAL ; 
 int pmic_read_temp (struct intel_pmic_opregion*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pmic_thermal_temp(struct intel_pmic_opregion *opregion, int reg,
			     u32 function, u64 *value)
{
	return function == ACPI_READ ?
		pmic_read_temp(opregion, reg, value) : -EINVAL;
}