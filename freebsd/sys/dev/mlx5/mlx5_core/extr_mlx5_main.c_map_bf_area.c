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
struct TYPE_2__ {int /*<<< orphan*/  bf_mapping; } ;
struct mlx5_core_dev {TYPE_1__ priv; int /*<<< orphan*/  pdev; } ;
typedef  int /*<<< orphan*/  resource_size_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  io_mapping_create_wc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int map_bf_area(struct mlx5_core_dev *dev)
{
	resource_size_t bf_start = pci_resource_start(dev->pdev, 0);
	resource_size_t bf_len = pci_resource_len(dev->pdev, 0);

	dev->priv.bf_mapping = io_mapping_create_wc(bf_start, bf_len);

	return dev->priv.bf_mapping ? 0 : -ENOMEM;
}