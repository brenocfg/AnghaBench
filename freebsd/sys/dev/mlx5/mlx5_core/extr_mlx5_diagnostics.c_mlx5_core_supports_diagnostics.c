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
typedef  scalar_t__ u16 ;
struct mlx5_core_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  counter_id; } ;

/* Variables and functions */
 scalar_t__ MLX5_CAP_DEBUG (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int MLX5_CAP_GEN (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug ; 
 TYPE_1__* diagnostic_counter ; 
 int /*<<< orphan*/  num_of_diagnostic_counters ; 

int mlx5_core_supports_diagnostics(struct mlx5_core_dev *dev, u16 counter_id)
{
	int numcounters;
	int x;

	if (MLX5_CAP_GEN(dev, debug) == 0)
		return 0;

	/* check for any counter */
	if (counter_id == 0)
		return 1;

	numcounters = MLX5_CAP_GEN(dev, num_of_diagnostic_counters);

	/* check if counter ID exists in debug capability */
	for (x = 0; x != numcounters; x++) {
		if (MLX5_CAP_DEBUG(dev, diagnostic_counter[x].counter_id) ==
		    counter_id)
			return 1;
	}
	return 0;			/* not supported counter */
}