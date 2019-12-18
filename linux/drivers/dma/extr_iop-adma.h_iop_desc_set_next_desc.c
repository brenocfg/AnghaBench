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
union iop3xx_desc {TYPE_1__* dma; int /*<<< orphan*/  ptr; } ;
typedef  int /*<<< orphan*/  u32 ;
struct iop_adma_desc_slot {int /*<<< orphan*/  hw_desc; } ;
struct TYPE_2__ {int /*<<< orphan*/  next_desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  iop_paranoia (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void iop_desc_set_next_desc(struct iop_adma_desc_slot *desc,
					u32 next_desc_addr)
{
	/* hw_desc->next_desc is the same location for all channels */
	union iop3xx_desc hw_desc = { .ptr = desc->hw_desc, };

	iop_paranoia(hw_desc.dma->next_desc);
	hw_desc.dma->next_desc = next_desc_addr;
}