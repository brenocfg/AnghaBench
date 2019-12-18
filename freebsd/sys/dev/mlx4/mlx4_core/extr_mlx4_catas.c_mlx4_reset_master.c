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
struct mlx4_dev {TYPE_1__* persist; } ;
struct TYPE_2__ {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx4_err (struct mlx4_dev*,char*) ; 
 scalar_t__ mlx4_is_master (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_report_internal_err_comm_event (struct mlx4_dev*) ; 
 int mlx4_reset (struct mlx4_dev*) ; 
 int /*<<< orphan*/  pci_channel_offline (int /*<<< orphan*/ ) ; 
 int read_vendor_id (struct mlx4_dev*) ; 

__attribute__((used)) static int mlx4_reset_master(struct mlx4_dev *dev)
{
	int err = 0;

	if (mlx4_is_master(dev))
		mlx4_report_internal_err_comm_event(dev);

	if (!pci_channel_offline(dev->persist->pdev)) {
		err = read_vendor_id(dev);
		/* If PCI can't be accessed to read vendor ID we assume that its
		 * link was disabled and chip was already reset.
		 */
		if (err)
			return 0;

		err = mlx4_reset(dev);
		if (err)
			mlx4_err(dev, "Fail to reset HCA\n");
	}

	return err;
}