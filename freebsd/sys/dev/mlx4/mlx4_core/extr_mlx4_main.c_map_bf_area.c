#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mlx4_priv {int /*<<< orphan*/  bf_mapping; } ;
struct TYPE_4__ {int num_uars; int /*<<< orphan*/  bf_reg_size; } ;
struct mlx4_dev {TYPE_2__ caps; TYPE_1__* persist; } ;
typedef  scalar_t__ resource_size_t ;
struct TYPE_3__ {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  io_mapping_create_wc (scalar_t__,scalar_t__) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 
 scalar_t__ pci_resource_len (int /*<<< orphan*/ ,int) ; 
 scalar_t__ pci_resource_start (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int map_bf_area(struct mlx4_dev *dev)
{
	struct mlx4_priv *priv = mlx4_priv(dev);
	resource_size_t bf_start;
	resource_size_t bf_len;
	int err = 0;

	if (!dev->caps.bf_reg_size)
		return -ENXIO;

	bf_start = pci_resource_start(dev->persist->pdev, 2) +
			(dev->caps.num_uars << PAGE_SHIFT);
	bf_len = pci_resource_len(dev->persist->pdev, 2) -
			(dev->caps.num_uars << PAGE_SHIFT);
	priv->bf_mapping = io_mapping_create_wc(bf_start, bf_len);
	if (!priv->bf_mapping)
		err = -ENOMEM;

	return err;
}