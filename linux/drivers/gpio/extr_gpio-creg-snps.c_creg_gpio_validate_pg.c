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
struct device {int dummy; } ;
struct creg_layout {int* bit_per_gpio; int* on; int* off; } ;
struct creg_gpio {struct creg_layout* layout; } ;

/* Variables and functions */
 int EINVAL ; 
 int GENMASK (int,int) ; 

__attribute__((used)) static int creg_gpio_validate_pg(struct device *dev, struct creg_gpio *hcg,
				 int i)
{
	const struct creg_layout *layout = hcg->layout;

	if (layout->bit_per_gpio[i] < 1 || layout->bit_per_gpio[i] > 8)
		return -EINVAL;

	/* Check that on valiue fits it's placeholder */
	if (GENMASK(31, layout->bit_per_gpio[i]) & layout->on[i])
		return -EINVAL;

	/* Check that off valiue fits it's placeholder */
	if (GENMASK(31, layout->bit_per_gpio[i]) & layout->off[i])
		return -EINVAL;

	if (layout->on[i] == layout->off[i])
		return -EINVAL;

	return 0;
}