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
struct owl_dma {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void dma_update(struct owl_dma *od, u32 reg, u32 val, bool state)
{
	u32 regval;

	regval = readl(od->base + reg);

	if (state)
		regval |= val;
	else
		regval &= ~val;

	writel(val, od->base + reg);
}