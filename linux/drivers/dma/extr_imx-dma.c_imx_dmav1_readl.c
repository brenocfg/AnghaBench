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
struct imxdma_engine {unsigned int base; } ;

/* Variables and functions */
 int __raw_readl (unsigned int) ; 

__attribute__((used)) static unsigned imx_dmav1_readl(struct imxdma_engine *imxdma, unsigned offset)
{
	return __raw_readl(imxdma->base + offset);
}