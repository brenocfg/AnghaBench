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
struct mlx5_core_dev {int /*<<< orphan*/  esw_ingress_root_ns; int /*<<< orphan*/  esw_egress_root_ns; int /*<<< orphan*/  fdb_root_ns; int /*<<< orphan*/  sniffer_tx_root_ns; int /*<<< orphan*/  sniffer_rx_root_ns; } ;

/* Variables and functions */
 int /*<<< orphan*/  cleanup_root_ns (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  cleanup_single_prio_root_ns (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 

void mlx5_cleanup_fs(struct mlx5_core_dev *dev)
{
	cleanup_root_ns(dev);
	cleanup_single_prio_root_ns(dev, dev->sniffer_rx_root_ns);
	cleanup_single_prio_root_ns(dev, dev->sniffer_tx_root_ns);
	cleanup_single_prio_root_ns(dev, dev->fdb_root_ns);
	cleanup_single_prio_root_ns(dev, dev->esw_egress_root_ns);
	cleanup_single_prio_root_ns(dev, dev->esw_ingress_root_ns);
}