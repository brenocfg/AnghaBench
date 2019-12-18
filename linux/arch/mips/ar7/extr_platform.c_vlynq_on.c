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
struct TYPE_2__ {struct plat_vlynq_data* platform_data; } ;
struct vlynq_device {TYPE_1__ dev; } ;
struct plat_vlynq_data {int /*<<< orphan*/  gpio_bit; int /*<<< orphan*/  reset_bit; } ;

/* Variables and functions */
 int /*<<< orphan*/  ar7_device_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar7_device_reset (int /*<<< orphan*/ ) ; 
 int ar7_gpio_disable (int /*<<< orphan*/ ) ; 
 int ar7_gpio_enable (int /*<<< orphan*/ ) ; 
 int gpio_direction_output (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int gpio_request (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int vlynq_on(struct vlynq_device *dev)
{
	int ret;
	struct plat_vlynq_data *pdata = dev->dev.platform_data;

	ret = gpio_request(pdata->gpio_bit, "vlynq");
	if (ret)
		goto out;

	ar7_device_reset(pdata->reset_bit);

	ret = ar7_gpio_disable(pdata->gpio_bit);
	if (ret)
		goto out_enabled;

	ret = ar7_gpio_enable(pdata->gpio_bit);
	if (ret)
		goto out_enabled;

	ret = gpio_direction_output(pdata->gpio_bit, 0);
	if (ret)
		goto out_gpio_enabled;

	msleep(50);

	gpio_set_value(pdata->gpio_bit, 1);

	msleep(50);

	return 0;

out_gpio_enabled:
	ar7_gpio_disable(pdata->gpio_bit);
out_enabled:
	ar7_device_disable(pdata->reset_bit);
	gpio_free(pdata->gpio_bit);
out:
	return ret;
}