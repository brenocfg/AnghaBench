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
struct imx_timer {scalar_t__ base; } ;

/* Variables and functions */
 unsigned int MX1_2_TCTL_IRQEN ; 
 scalar_t__ MXC_TCTL ; 
 unsigned int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (unsigned int,scalar_t__) ; 

__attribute__((used)) static void imx1_gpt_irq_enable(struct imx_timer *imxtm)
{
	unsigned int tmp;

	tmp = readl_relaxed(imxtm->base + MXC_TCTL);
	writel_relaxed(tmp | MX1_2_TCTL_IRQEN, imxtm->base + MXC_TCTL);
}