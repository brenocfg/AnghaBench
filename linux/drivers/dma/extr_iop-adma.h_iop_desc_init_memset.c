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
struct iop_adma_desc_slot {struct iop3xx_desc_aau* hw_desc; } ;
struct iop3xx_desc_aau {scalar_t__ desc_ctrl; } ;
struct iop3xx_aau_desc_ctrl {int blk1_cmd_ctrl; int dest_write_en; unsigned long int_en; } ;

/* Variables and functions */
 unsigned long DMA_PREP_INTERRUPT ; 

__attribute__((used)) static inline void
iop_desc_init_memset(struct iop_adma_desc_slot *desc, unsigned long flags)
{
	struct iop3xx_desc_aau *hw_desc = desc->hw_desc;
	union {
		u32 value;
		struct iop3xx_aau_desc_ctrl field;
	} u_desc_ctrl;

	u_desc_ctrl.value = 0;
	u_desc_ctrl.field.blk1_cmd_ctrl = 0x2; /* memory block fill */
	u_desc_ctrl.field.dest_write_en = 1;
	u_desc_ctrl.field.int_en = flags & DMA_PREP_INTERRUPT;
	hw_desc->desc_ctrl = u_desc_ctrl.value;
}