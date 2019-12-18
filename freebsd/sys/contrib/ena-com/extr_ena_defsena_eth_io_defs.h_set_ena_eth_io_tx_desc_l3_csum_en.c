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
typedef  int uint32_t ;
struct ena_eth_io_tx_desc {int meta_ctrl; } ;

/* Variables and functions */
 int ENA_ETH_IO_TX_DESC_L3_CSUM_EN_MASK ; 
 int ENA_ETH_IO_TX_DESC_L3_CSUM_EN_SHIFT ; 

__attribute__((used)) static inline void set_ena_eth_io_tx_desc_l3_csum_en(struct ena_eth_io_tx_desc *p, uint32_t val)
{
	p->meta_ctrl |= (val << ENA_ETH_IO_TX_DESC_L3_CSUM_EN_SHIFT) & ENA_ETH_IO_TX_DESC_L3_CSUM_EN_MASK;
}