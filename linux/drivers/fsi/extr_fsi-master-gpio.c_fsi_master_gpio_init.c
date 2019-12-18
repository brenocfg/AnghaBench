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
struct fsi_master_gpio {int /*<<< orphan*/  gpio_data; int /*<<< orphan*/  gpio_clk; int /*<<< orphan*/  gpio_enable; int /*<<< orphan*/  gpio_trans; int /*<<< orphan*/  gpio_mux; } ;

/* Variables and functions */
 int /*<<< orphan*/  FSI_INIT_CLOCKS ; 
 int /*<<< orphan*/  clock_zeros (struct fsi_master_gpio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_direction_output (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

__attribute__((used)) static void fsi_master_gpio_init(struct fsi_master_gpio *master)
{
	unsigned long flags;

	gpiod_direction_output(master->gpio_mux, 1);
	gpiod_direction_output(master->gpio_trans, 1);
	gpiod_direction_output(master->gpio_enable, 1);
	gpiod_direction_output(master->gpio_clk, 1);
	gpiod_direction_output(master->gpio_data, 1);

	/* todo: evaluate if clocks can be reduced */
	local_irq_save(flags);
	clock_zeros(master, FSI_INIT_CLOCKS);
	local_irq_restore(flags);
}