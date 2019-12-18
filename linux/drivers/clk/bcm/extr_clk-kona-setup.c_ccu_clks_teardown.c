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
typedef  size_t u32 ;
struct ccu_data {size_t clk_num; TYPE_1__* kona_clks; } ;
struct TYPE_2__ {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  kona_clk_teardown (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ccu_clks_teardown(struct ccu_data *ccu)
{
	u32 i;

	for (i = 0; i < ccu->clk_num; i++)
		kona_clk_teardown(&ccu->kona_clks[i].hw);
}