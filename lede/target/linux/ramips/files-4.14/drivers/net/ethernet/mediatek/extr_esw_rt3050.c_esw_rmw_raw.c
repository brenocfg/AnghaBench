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
struct rt305x_esw {unsigned int base; } ;

/* Variables and functions */
 unsigned long __raw_readl (unsigned int) ; 
 int /*<<< orphan*/  __raw_writel (unsigned long,unsigned int) ; 

__attribute__((used)) static inline void esw_rmw_raw(struct rt305x_esw *esw, unsigned reg,
			       unsigned long mask, unsigned long val)
{
	unsigned long t;

	t = __raw_readl(esw->base + reg) & ~mask;
	__raw_writel(t | val, esw->base + reg);
}