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
typedef  unsigned int uint32_t ;
typedef  int u32 ;
struct ag71xx {unsigned int mac_base; } ;

/* Variables and functions */
 int __raw_readl (unsigned int) ; 
 int /*<<< orphan*/  __raw_writel (int,unsigned int) ; 

__attribute__((used)) static inline void ag71xx_sb(struct ag71xx *ag, unsigned reg, u32 mask)
{
	uint32_t r;

	r = ag->mac_base + reg;
	__raw_writel(__raw_readl(r) | mask, r);
	/* flush write */
	(void)__raw_readl(r);
}