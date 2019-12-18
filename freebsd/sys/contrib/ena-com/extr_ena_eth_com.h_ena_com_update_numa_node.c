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
typedef  int u8 ;
struct ena_eth_io_numa_node_cfg_reg {int numa_cfg; } ;
struct ena_com_io_cq {int /*<<< orphan*/  numa_node_cfg_reg; int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int ENA_ETH_IO_NUMA_NODE_CFG_REG_ENABLED_MASK ; 
 int ENA_ETH_IO_NUMA_NODE_CFG_REG_NUMA_MASK ; 
 int /*<<< orphan*/  ENA_REG_WRITE32 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ena_com_update_numa_node(struct ena_com_io_cq *io_cq,
					    u8 numa_node)
{
	struct ena_eth_io_numa_node_cfg_reg numa_cfg;

	if (!io_cq->numa_node_cfg_reg)
		return;

	numa_cfg.numa_cfg = (numa_node & ENA_ETH_IO_NUMA_NODE_CFG_REG_NUMA_MASK)
		| ENA_ETH_IO_NUMA_NODE_CFG_REG_ENABLED_MASK;

	ENA_REG_WRITE32(io_cq->bus, numa_cfg.numa_cfg, io_cq->numa_node_cfg_reg);
}