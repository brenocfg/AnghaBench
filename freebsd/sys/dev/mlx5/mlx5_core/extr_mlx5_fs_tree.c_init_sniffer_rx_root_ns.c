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
struct mlx5_core_dev {TYPE_1__* sniffer_rx_root_ns; } ;
struct fs_prio {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ns; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FS_FT_SNIFFER_RX ; 
 scalar_t__ IS_ERR (struct fs_prio*) ; 
 int /*<<< orphan*/  MLX5_CORE_FS_SNIFFER_RX_ROOT_NS_NAME ; 
 int PTR_ERR (struct fs_prio*) ; 
 TYPE_1__* create_root_ns (struct mlx5_core_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fs_prio* fs_create_prio (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int init_sniffer_rx_root_ns(struct mlx5_core_dev *dev)
{
	struct fs_prio *prio;

	dev->sniffer_rx_root_ns = create_root_ns(dev, FS_FT_SNIFFER_RX,
				     MLX5_CORE_FS_SNIFFER_RX_ROOT_NS_NAME);
	if (!dev->sniffer_rx_root_ns)
		return  -ENOMEM;

	/* create 1 prio*/
	prio = fs_create_prio(&dev->sniffer_rx_root_ns->ns, 0, 1,
			      "sniffer_prio", 0);
	if (IS_ERR(prio))
		return PTR_ERR(prio);
	else
		return 0;
}