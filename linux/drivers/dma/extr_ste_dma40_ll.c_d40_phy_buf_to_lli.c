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
typedef  int u32 ;
struct stedma40_half_channel_info {int /*<<< orphan*/  data_width; } ;
struct d40_phy_lli {int dummy; } ;
typedef  int dma_addr_t ;

/* Variables and functions */
 int ALIGN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  D40_LLI_ALIGN ; 
 unsigned long LLI_ADDR_INC ; 
 unsigned long LLI_CYCLIC ; 
 unsigned long LLI_LAST_LINK ; 
 unsigned long LLI_TERM_INT ; 
 int d40_phy_fill_lli (struct d40_phy_lli*,int,int,int,int,struct stedma40_half_channel_info*,unsigned long) ; 
 int d40_seg_size (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct d40_phy_lli *
d40_phy_buf_to_lli(struct d40_phy_lli *lli, dma_addr_t addr, u32 size,
		   dma_addr_t lli_phys, dma_addr_t first_phys, u32 reg_cfg,
		   struct stedma40_half_channel_info *info,
		   struct stedma40_half_channel_info *otherinfo,
		   unsigned long flags)
{
	bool lastlink = flags & LLI_LAST_LINK;
	bool addr_inc = flags & LLI_ADDR_INC;
	bool term_int = flags & LLI_TERM_INT;
	bool cyclic = flags & LLI_CYCLIC;
	int err;
	dma_addr_t next = lli_phys;
	int size_rest = size;
	int size_seg = 0;

	/*
	 * This piece may be split up based on d40_seg_size(); we only want the
	 * term int on the last part.
	 */
	if (term_int)
		flags &= ~LLI_TERM_INT;

	do {
		size_seg = d40_seg_size(size_rest, info->data_width,
					otherinfo->data_width);
		size_rest -= size_seg;

		if (size_rest == 0 && term_int)
			flags |= LLI_TERM_INT;

		if (size_rest == 0 && lastlink)
			next = cyclic ? first_phys : 0;
		else
			next = ALIGN(next + sizeof(struct d40_phy_lli),
				     D40_LLI_ALIGN);

		err = d40_phy_fill_lli(lli, addr, size_seg, next,
				       reg_cfg, info, flags);

		if (err)
			goto err;

		lli++;
		if (addr_inc)
			addr += size_seg;
	} while (size_rest);

	return lli;

err:
	return NULL;
}