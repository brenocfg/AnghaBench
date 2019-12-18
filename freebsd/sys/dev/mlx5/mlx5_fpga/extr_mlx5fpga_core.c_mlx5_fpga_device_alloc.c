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
struct mlx5_fpga_device {int /*<<< orphan*/  client_data_list; int /*<<< orphan*/  fdev_state; int /*<<< orphan*/  load_event; int /*<<< orphan*/  state_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MLX5_FDEV_STATE_NONE ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 struct mlx5_fpga_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct mlx5_fpga_device *mlx5_fpga_device_alloc(void)
{
	struct mlx5_fpga_device *fdev = NULL;

	fdev = kzalloc(sizeof(*fdev), GFP_KERNEL);
	if (!fdev)
		return NULL;

	spin_lock_init(&fdev->state_lock);
	init_completion(&fdev->load_event);
	fdev->fdev_state = MLX5_FDEV_STATE_NONE;
	INIT_LIST_HEAD(&fdev->client_data_list);
	return fdev;
}