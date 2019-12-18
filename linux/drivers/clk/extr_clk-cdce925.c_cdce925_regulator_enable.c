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
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct regulator*) ; 
 int PTR_ERR (struct regulator*) ; 
 int /*<<< orphan*/  cdce925_regulator_disable ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,char const*,int) ; 
 int devm_add_action_or_reset (struct device*,int /*<<< orphan*/ ,struct regulator*) ; 
 struct regulator* devm_regulator_get (struct device*,char const*) ; 
 int regulator_enable (struct regulator*) ; 

__attribute__((used)) static int cdce925_regulator_enable(struct device *dev, const char *name)
{
	struct regulator *regulator;
	int err;

	regulator = devm_regulator_get(dev, name);
	if (IS_ERR(regulator))
		return PTR_ERR(regulator);

	err = regulator_enable(regulator);
	if (err) {
		dev_err(dev, "Failed to enable %s: %d\n", name, err);
		return err;
	}

	return devm_add_action_or_reset(dev, cdce925_regulator_disable,
					regulator);
}