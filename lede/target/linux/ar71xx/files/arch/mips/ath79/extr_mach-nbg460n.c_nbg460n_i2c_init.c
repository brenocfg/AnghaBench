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
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_register_board_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nbg460n_i2c_device ; 
 int /*<<< orphan*/  nbg460n_i2c_devs ; 
 int /*<<< orphan*/  platform_device_register (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nbg460n_i2c_init(void)
{
	/* The gpio interface */
	platform_device_register(&nbg460n_i2c_device);
	/* I2C devices */
	i2c_register_board_info(0, nbg460n_i2c_devs,
				ARRAY_SIZE(nbg460n_i2c_devs));
}