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
struct timer_of {int dummy; } ;
struct clock_event_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ NPCM7XX_REG_TCSR0 ; 
 int /*<<< orphan*/  NPCM7XX_START_ONESHOT_Tx ; 
 int /*<<< orphan*/  NPCM7XX_Tx_OPER ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 scalar_t__ timer_of_base (struct timer_of*) ; 
 struct timer_of* to_timer_of (struct clock_event_device*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int npcm7xx_timer_oneshot(struct clock_event_device *evt)
{
	struct timer_of *to = to_timer_of(evt);
	u32 val;

	val = readl(timer_of_base(to) + NPCM7XX_REG_TCSR0);
	val &= ~NPCM7XX_Tx_OPER;
	val |= NPCM7XX_START_ONESHOT_Tx;
	writel(val, timer_of_base(to) + NPCM7XX_REG_TCSR0);

	return 0;
}