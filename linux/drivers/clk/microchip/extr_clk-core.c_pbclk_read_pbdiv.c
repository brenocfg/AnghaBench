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
struct pic32_periph_clk {int /*<<< orphan*/  ctrl_reg; } ;

/* Variables and functions */
 int PB_DIV_MASK ; 
 int PB_DIV_SHIFT ; 
 int readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 pbclk_read_pbdiv(struct pic32_periph_clk *pb)
{
	return ((readl(pb->ctrl_reg) >> PB_DIV_SHIFT) & PB_DIV_MASK) + 1;
}