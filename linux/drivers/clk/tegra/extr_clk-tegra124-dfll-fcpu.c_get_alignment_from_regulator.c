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
struct regulator {int dummy; } ;
struct rail_alignment {int /*<<< orphan*/  step_uv; int /*<<< orphan*/  offset_uv; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct regulator*) ; 
 int PTR_ERR (struct regulator*) ; 
 struct regulator* devm_regulator_get (struct device*,char*) ; 
 int /*<<< orphan*/  devm_regulator_put (struct regulator*) ; 
 int /*<<< orphan*/  regulator_get_linear_step (struct regulator*) ; 
 int /*<<< orphan*/  regulator_list_voltage (struct regulator*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_alignment_from_regulator(struct device *dev,
					 struct rail_alignment *align)
{
	struct regulator *reg = devm_regulator_get(dev, "vdd-cpu");

	if (IS_ERR(reg))
		return PTR_ERR(reg);

	align->offset_uv = regulator_list_voltage(reg, 0);
	align->step_uv = regulator_get_linear_step(reg);

	devm_regulator_put(reg);

	return 0;
}