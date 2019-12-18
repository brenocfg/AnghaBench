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
typedef  int u8 ;
struct mlx5_core_dev {TYPE_1__* iseg; } ;
struct TYPE_2__ {int /*<<< orphan*/  cmdq_addr_l_sz; } ;

/* Variables and functions */
 int ioread32be (int /*<<< orphan*/ *) ; 

u8 mlx5_get_nic_state(struct mlx5_core_dev *dev)
{
	return (ioread32be(&dev->iseg->cmdq_addr_l_sz) >> 8) & 7;
}