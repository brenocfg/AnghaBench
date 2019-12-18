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
typedef  int /*<<< orphan*/  s8 ;

/* Variables and functions */
 int DMA_CHAN_CFG_DST_DRQ_H6 (int /*<<< orphan*/ ) ; 
 int DMA_CHAN_CFG_SRC_DRQ_H6 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sun6i_set_drq_h6(u32 *p_cfg, s8 src_drq, s8 dst_drq)
{
	*p_cfg |= DMA_CHAN_CFG_SRC_DRQ_H6(src_drq) |
		  DMA_CHAN_CFG_DST_DRQ_H6(dst_drq);
}