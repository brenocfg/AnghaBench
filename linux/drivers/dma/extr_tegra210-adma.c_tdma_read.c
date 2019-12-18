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
typedef  scalar_t__ u32 ;
struct tegra_adma {TYPE_1__* cdata; scalar_t__ base_addr; } ;
struct TYPE_2__ {scalar_t__ global_reg_offset; } ;

/* Variables and functions */
 scalar_t__ readl (scalar_t__) ; 

__attribute__((used)) static inline u32 tdma_read(struct tegra_adma *tdma, u32 reg)
{
	return readl(tdma->base_addr + tdma->cdata->global_reg_offset + reg);
}