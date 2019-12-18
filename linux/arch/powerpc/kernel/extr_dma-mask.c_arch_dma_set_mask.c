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
typedef  int /*<<< orphan*/  u64 ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* dma_set_mask ) (struct device*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_1__ ppc_md ; 
 int /*<<< orphan*/  stub1 (struct device*,int /*<<< orphan*/ ) ; 

void arch_dma_set_mask(struct device *dev, u64 dma_mask)
{
	if (ppc_md.dma_set_mask)
		ppc_md.dma_set_mask(dev, dma_mask);
}