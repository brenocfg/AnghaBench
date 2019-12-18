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
struct ena_eth_io_tx_meta_desc {int word1; } ;

/* Variables and functions */
 int ENA_ETH_IO_TX_META_DESC_REQ_ID_HI_MASK ; 

__attribute__((used)) static inline void set_ena_eth_io_tx_meta_desc_req_id_hi(struct ena_eth_io_tx_meta_desc *p, uint32_t val)
{
	p->word1 |= val & ENA_ETH_IO_TX_META_DESC_REQ_ID_HI_MASK;
}