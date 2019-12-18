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
struct TYPE_2__ {scalar_t__ base; } ;

/* Variables and functions */
 TYPE_1__ dscr ; 
 int /*<<< orphan*/  soc_writel (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void dscr_write_locked2(u32 reg, u32 val,
			       u32 lock0, u32 key0,
			       u32 lock1, u32 key1)
{
	soc_writel(key0, dscr.base + lock0);
	soc_writel(key1, dscr.base + lock1);
	soc_writel(val, dscr.base + reg);
	soc_writel(0, dscr.base + lock0);
	soc_writel(0, dscr.base + lock1);
}