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
struct ag71xx {int /*<<< orphan*/  mii_ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ag71xx_mii_ctrl_wr(struct ag71xx *ag, u32 value)
{
	__raw_writel(value, ag->mii_ctrl);

	/* flush write */
	__raw_readl(ag->mii_ctrl);
}