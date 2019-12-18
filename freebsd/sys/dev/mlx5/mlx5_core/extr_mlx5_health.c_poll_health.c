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
typedef  scalar_t__ u32 ;
struct mlx5_core_health {scalar_t__ prev; scalar_t__ miss_counter; int /*<<< orphan*/  timer; scalar_t__ fatal_error; int /*<<< orphan*/  health_counter; } ;
struct TYPE_2__ {struct mlx5_core_health health; } ;
struct mlx5_core_dev {scalar_t__ state; TYPE_1__ priv; } ;

/* Variables and functions */
 scalar_t__ MAX_MISSES ; 
 scalar_t__ MLX5_DEVICE_STATE_UP ; 
 scalar_t__ check_fatal_sensors (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  get_next_poll_jiffies () ; 
 scalar_t__ ioread32be (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_core_err (struct mlx5_core_dev*,char*,...) ; 
 int /*<<< orphan*/  mlx5_trigger_health_work (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ print_health_info (struct mlx5_core_dev*) ; 

__attribute__((used)) static void poll_health(unsigned long data)
{
	struct mlx5_core_dev *dev = (struct mlx5_core_dev *)data;
	struct mlx5_core_health *health = &dev->priv.health;
	u32 fatal_error;
	u32 count;

	if (dev->state != MLX5_DEVICE_STATE_UP)
		return;

	count = ioread32be(health->health_counter);
	if (count == health->prev)
		++health->miss_counter;
	else
		health->miss_counter = 0;

	health->prev = count;
	if (health->miss_counter == MAX_MISSES) {
		mlx5_core_err(dev, "device's health compromised - reached miss count\n");
		if (print_health_info(dev) == 0)
			mlx5_core_err(dev, "FW is unable to respond to initialization segment reads\n");
	}

	fatal_error = check_fatal_sensors(dev);

	if (fatal_error && !health->fatal_error) {
		mlx5_core_err(dev,
		    "Fatal error %u detected\n", fatal_error);
		dev->priv.health.fatal_error = fatal_error;
		print_health_info(dev);
		mlx5_trigger_health_work(dev);
	}

	mod_timer(&health->timer, get_next_poll_jiffies());
}