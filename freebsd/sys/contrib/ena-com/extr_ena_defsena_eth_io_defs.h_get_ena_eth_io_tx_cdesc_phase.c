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
struct ena_eth_io_tx_cdesc {int flags; } ;

/* Variables and functions */
 int ENA_ETH_IO_TX_CDESC_PHASE_MASK ; 

__attribute__((used)) static inline uint8_t get_ena_eth_io_tx_cdesc_phase(const struct ena_eth_io_tx_cdesc *p)
{
	return p->flags & ENA_ETH_IO_TX_CDESC_PHASE_MASK;
}