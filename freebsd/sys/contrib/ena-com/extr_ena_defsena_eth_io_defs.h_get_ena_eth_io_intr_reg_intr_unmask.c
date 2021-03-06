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
struct ena_eth_io_intr_reg {int intr_control; } ;

/* Variables and functions */
 int ENA_ETH_IO_INTR_REG_INTR_UNMASK_MASK ; 
 int ENA_ETH_IO_INTR_REG_INTR_UNMASK_SHIFT ; 

__attribute__((used)) static inline uint32_t get_ena_eth_io_intr_reg_intr_unmask(const struct ena_eth_io_intr_reg *p)
{
	return (p->intr_control & ENA_ETH_IO_INTR_REG_INTR_UNMASK_MASK) >> ENA_ETH_IO_INTR_REG_INTR_UNMASK_SHIFT;
}