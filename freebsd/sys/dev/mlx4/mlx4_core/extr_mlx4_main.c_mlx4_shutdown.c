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
struct pci_dev {int dummy; } ;
struct mlx4_dev_persistent {int interface_state; int /*<<< orphan*/  interface_state_mutex; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int MLX4_INTERFACE_STATE_UP ; 
 int /*<<< orphan*/  mlx4_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlx4_unload_one (struct pci_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct mlx4_dev_persistent* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static void mlx4_shutdown(struct pci_dev *pdev)
{
	struct mlx4_dev_persistent *persist = pci_get_drvdata(pdev);

	mlx4_info(persist->dev, "mlx4_shutdown was called\n");
	mutex_lock(&persist->interface_state_mutex);
	if (persist->interface_state & MLX4_INTERFACE_STATE_UP)
		mlx4_unload_one(pdev);
	mutex_unlock(&persist->interface_state_mutex);
}