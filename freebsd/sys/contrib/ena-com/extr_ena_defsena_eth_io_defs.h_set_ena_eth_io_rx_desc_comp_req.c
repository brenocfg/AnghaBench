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
typedef  int uint8_t ;
struct ena_eth_io_rx_desc {int ctrl; } ;

/* Variables and functions */
 int ENA_ETH_IO_RX_DESC_COMP_REQ_MASK ; 
 int ENA_ETH_IO_RX_DESC_COMP_REQ_SHIFT ; 

__attribute__((used)) static inline void set_ena_eth_io_rx_desc_comp_req(struct ena_eth_io_rx_desc *p, uint8_t val)
{
	p->ctrl |= (val << ENA_ETH_IO_RX_DESC_COMP_REQ_SHIFT) & ENA_ETH_IO_RX_DESC_COMP_REQ_MASK;
}