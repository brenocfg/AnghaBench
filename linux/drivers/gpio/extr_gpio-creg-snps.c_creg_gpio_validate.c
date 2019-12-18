#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct device {int dummy; } ;
struct creg_gpio {TYPE_1__* layout; } ;
struct TYPE_2__ {int ngpio; scalar_t__* bit_per_gpio; scalar_t__* shift; } ;

/* Variables and functions */
 int EINVAL ; 
 int MAX_GPIO ; 
 scalar_t__ creg_gpio_validate_pg (struct device*,struct creg_gpio*,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 

__attribute__((used)) static int creg_gpio_validate(struct device *dev, struct creg_gpio *hcg,
			      u32 ngpios)
{
	u32 reg_len = 0;
	int i;

	if (hcg->layout->ngpio < 1 || hcg->layout->ngpio > MAX_GPIO)
		return -EINVAL;

	if (ngpios < 1 || ngpios > hcg->layout->ngpio) {
		dev_err(dev, "ngpios must be in [1:%u]\n", hcg->layout->ngpio);
		return -EINVAL;
	}

	for (i = 0; i < hcg->layout->ngpio; i++) {
		if (creg_gpio_validate_pg(dev, hcg, i))
			return -EINVAL;

		reg_len += hcg->layout->shift[i] + hcg->layout->bit_per_gpio[i];
	}

	/* Check that we fit in 32 bit register */
	if (reg_len > 32)
		return -EINVAL;

	return 0;
}