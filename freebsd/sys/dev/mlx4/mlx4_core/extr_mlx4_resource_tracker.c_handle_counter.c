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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {scalar_t__ counter_index; } ;
struct mlx4_qp_context {TYPE_1__ pri_path; } ;
struct mlx4_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ MLX4_SINK_COUNTER_INDEX (struct mlx4_dev*) ; 
 int handle_existing_counter (struct mlx4_dev*,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int handle_unexisting_counter (struct mlx4_dev*,struct mlx4_qp_context*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int handle_counter(struct mlx4_dev *dev, struct mlx4_qp_context *qpc,
			  u8 slave, int port)
{
	if (qpc->pri_path.counter_index != MLX4_SINK_COUNTER_INDEX(dev))
		return handle_existing_counter(dev, slave, port,
					       qpc->pri_path.counter_index);

	return handle_unexisting_counter(dev, qpc, slave, port);
}