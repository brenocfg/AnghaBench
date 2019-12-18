#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {scalar_t__ smca; } ;
struct TYPE_3__ {int (* misc ) (unsigned int) ;} ;

/* Variables and functions */
 int MASK_BLKPTR_LO ; 
 int MCG_XBLK_ADDR ; 
 unsigned int NR_BLOCKS ; 
 TYPE_2__ mce_flags ; 
 int /*<<< orphan*/  mce_num_banks ; 
 TYPE_1__ msr_ops ; 
 unsigned int per_cpu (int /*<<< orphan*/ ,unsigned int) ; 
 int smca_get_block_address (unsigned int,unsigned int,unsigned int) ; 
 int stub1 (unsigned int) ; 

__attribute__((used)) static u32 get_block_address(u32 current_addr, u32 low, u32 high,
			     unsigned int bank, unsigned int block,
			     unsigned int cpu)
{
	u32 addr = 0, offset = 0;

	if ((bank >= per_cpu(mce_num_banks, cpu)) || (block >= NR_BLOCKS))
		return addr;

	if (mce_flags.smca)
		return smca_get_block_address(bank, block, cpu);

	/* Fall back to method we used for older processors: */
	switch (block) {
	case 0:
		addr = msr_ops.misc(bank);
		break;
	case 1:
		offset = ((low & MASK_BLKPTR_LO) >> 21);
		if (offset)
			addr = MCG_XBLK_ADDR + offset;
		break;
	default:
		addr = ++current_addr;
	}
	return addr;
}