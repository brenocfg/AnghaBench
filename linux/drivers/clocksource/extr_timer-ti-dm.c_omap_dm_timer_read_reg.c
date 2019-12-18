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
struct omap_dm_timer {int /*<<< orphan*/  posted; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int _OMAP_TIMER_WAKEUP_EN_OFFSET ; 
 int __omap_dm_timer_read (struct omap_dm_timer*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 omap_dm_timer_read_reg(struct omap_dm_timer *timer, u32 reg)
{
	WARN_ON((reg & 0xff) < _OMAP_TIMER_WAKEUP_EN_OFFSET);
	return __omap_dm_timer_read(timer, reg, timer->posted);
}