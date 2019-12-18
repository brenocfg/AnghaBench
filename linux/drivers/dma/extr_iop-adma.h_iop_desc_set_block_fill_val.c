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
typedef  int /*<<< orphan*/  u32 ;
struct iop_adma_desc_slot {struct iop3xx_desc_aau* hw_desc; } ;
struct iop3xx_desc_aau {int /*<<< orphan*/ * src; } ;

/* Variables and functions */

__attribute__((used)) static inline void iop_desc_set_block_fill_val(struct iop_adma_desc_slot *desc,
						u32 val)
{
	struct iop3xx_desc_aau *hw_desc = desc->hw_desc;
	hw_desc->src[0] = val;
}