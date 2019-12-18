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
struct fsi_master_acf {int /*<<< orphan*/  gpio_trans; int /*<<< orphan*/  gpio_data; int /*<<< orphan*/  gpio_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  aspeed_gpio_copro_release_gpio (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void release_copro_gpios(struct fsi_master_acf *master)
{
	aspeed_gpio_copro_release_gpio(master->gpio_clk);
	aspeed_gpio_copro_release_gpio(master->gpio_data);
	aspeed_gpio_copro_release_gpio(master->gpio_trans);
}