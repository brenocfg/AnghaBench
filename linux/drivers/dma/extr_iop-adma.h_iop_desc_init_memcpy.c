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
typedef  scalar_t__ u32 ;
struct iop_adma_desc_slot {struct iop3xx_desc_dma* hw_desc; } ;
struct iop3xx_dma_desc_ctrl {int mem_to_mem_en; int pci_transaction; unsigned long int_en; } ;
struct iop3xx_desc_dma {scalar_t__ crc_addr; scalar_t__ upper_pci_src_addr; scalar_t__ desc_ctrl; } ;

/* Variables and functions */
 unsigned long DMA_PREP_INTERRUPT ; 

__attribute__((used)) static inline void
iop_desc_init_memcpy(struct iop_adma_desc_slot *desc, unsigned long flags)
{
	struct iop3xx_desc_dma *hw_desc = desc->hw_desc;
	union {
		u32 value;
		struct iop3xx_dma_desc_ctrl field;
	} u_desc_ctrl;

	u_desc_ctrl.value = 0;
	u_desc_ctrl.field.mem_to_mem_en = 1;
	u_desc_ctrl.field.pci_transaction = 0xe; /* memory read block */
	u_desc_ctrl.field.int_en = flags & DMA_PREP_INTERRUPT;
	hw_desc->desc_ctrl = u_desc_ctrl.value;
	hw_desc->upper_pci_src_addr = 0;
	hw_desc->crc_addr = 0;
}