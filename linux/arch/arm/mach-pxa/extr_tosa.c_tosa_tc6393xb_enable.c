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
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TOSA_GPIO_TC6393XB_L3V_ON ; 
 int /*<<< orphan*/  TOSA_GPIO_TC6393XB_REST_IN ; 
 int /*<<< orphan*/  TOSA_GPIO_TC6393XB_SUSPEND ; 
 int gpio_direction_output (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int gpio_request (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static int tosa_tc6393xb_enable(struct platform_device *dev)
{
	int rc;

	rc = gpio_request(TOSA_GPIO_TC6393XB_REST_IN, "tc6393xb #pclr");
	if (rc)
		goto err_req_pclr;
	rc = gpio_request(TOSA_GPIO_TC6393XB_SUSPEND, "tc6393xb #suspend");
	if (rc)
		goto err_req_suspend;
	rc = gpio_request(TOSA_GPIO_TC6393XB_L3V_ON, "tc6393xb l3v");
	if (rc)
		goto err_req_l3v;
	rc = gpio_direction_output(TOSA_GPIO_TC6393XB_L3V_ON, 0);
	if (rc)
		goto err_dir_l3v;
	rc = gpio_direction_output(TOSA_GPIO_TC6393XB_SUSPEND, 0);
	if (rc)
		goto err_dir_suspend;
	rc = gpio_direction_output(TOSA_GPIO_TC6393XB_REST_IN, 0);
	if (rc)
		goto err_dir_pclr;

	mdelay(1);

	gpio_set_value(TOSA_GPIO_TC6393XB_SUSPEND, 1);

	mdelay(10);

	gpio_set_value(TOSA_GPIO_TC6393XB_REST_IN, 1);
	gpio_set_value(TOSA_GPIO_TC6393XB_L3V_ON, 1);

	return 0;
err_dir_pclr:
err_dir_suspend:
err_dir_l3v:
	gpio_free(TOSA_GPIO_TC6393XB_L3V_ON);
err_req_l3v:
	gpio_free(TOSA_GPIO_TC6393XB_SUSPEND);
err_req_suspend:
	gpio_free(TOSA_GPIO_TC6393XB_REST_IN);
err_req_pclr:
	return rc;
}