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
struct mlx5_core_health {int last_reset_req; } ;
struct TYPE_2__ {struct mlx5_core_health health; } ;
struct mlx5_core_dev {TYPE_1__ priv; } ;

/* Variables and functions */
 unsigned int hz ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*) ; 
 unsigned int sw_reset_to ; 
 unsigned int ticks ; 

__attribute__((used)) static bool
mlx5_health_allow_reset(struct mlx5_core_dev *dev)
{
	struct mlx5_core_health *health = &dev->priv.health;
	unsigned int delta;
	bool ret;

	if (health->last_reset_req != 0) {
		delta = ticks - health->last_reset_req;
		delta /= hz;
		ret = delta >= sw_reset_to;
	} else {
		ret = true;
	}

	/*
	 * In principle, ticks may be 0. Setting it to off by one (-1)
	 * to prevent certain reset in next request.
	 */
	health->last_reset_req = ticks ? : -1;
	if (!ret)
		mlx5_core_warn(dev,
		    "Firmware reset elided due to auto-reset frequency threshold.\n");
	return (ret);
}