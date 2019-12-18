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
struct k3_dma_phy {int idx; } ;
struct k3_dma_dev {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ CX_CUR_CNT ; 
 int readl_relaxed (scalar_t__) ; 

__attribute__((used)) static u32 k3_dma_get_curr_cnt(struct k3_dma_dev *d, struct k3_dma_phy *phy)
{
	u32 cnt = 0;

	cnt = readl_relaxed(d->base + CX_CUR_CNT + phy->idx * 0x10);
	cnt &= 0xffff;
	return cnt;
}