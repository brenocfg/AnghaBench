#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct mlx4_dev {TYPE_1__* persist; } ;
struct TYPE_5__ {int toggle; scalar_t__ hcr; } ;
struct TYPE_6__ {TYPE_2__ cmd; } ;
struct TYPE_4__ {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int EIO ; 
 int HCR_GO_BIT ; 
 scalar_t__ HCR_STATUS_OFFSET ; 
 int HCR_T_BIT ; 
 TYPE_3__* mlx4_priv (struct mlx4_dev*) ; 
 scalar_t__ pci_channel_offline (int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int swab32 (int) ; 

__attribute__((used)) static int cmd_pending(struct mlx4_dev *dev)
{
	u32 status;

	if (pci_channel_offline(dev->persist->pdev))
		return -EIO;

	status = readl(mlx4_priv(dev)->cmd.hcr + HCR_STATUS_OFFSET);

	return (status & swab32(1 << HCR_GO_BIT)) ||
		(mlx4_priv(dev)->cmd.toggle ==
		 !!(status & swab32(1 << HCR_T_BIT)));
}