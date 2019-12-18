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
 int /*<<< orphan*/  COLLIE_GPIO_VPEN ; 
 int gpio_direction_output (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int gpio_request (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int collie_flash_init(void)
{
	int rc = gpio_request(COLLIE_GPIO_VPEN, "flash Vpp enable");
	if (rc)
		return rc;

	rc = gpio_direction_output(COLLIE_GPIO_VPEN, 1);
	if (rc)
		gpio_free(COLLIE_GPIO_VPEN);

	return rc;
}