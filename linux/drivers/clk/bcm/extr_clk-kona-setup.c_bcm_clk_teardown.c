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
struct TYPE_2__ {int /*<<< orphan*/ * data; } ;
struct kona_clk {int type; TYPE_1__ u; int /*<<< orphan*/  init_data; } ;

/* Variables and functions */
 int bcm_clk_none ; 
#define  bcm_clk_peri 128 
 int /*<<< orphan*/  peri_clk_teardown (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bcm_clk_teardown(struct kona_clk *bcm_clk)
{
	switch (bcm_clk->type) {
	case bcm_clk_peri:
		peri_clk_teardown(bcm_clk->u.data, &bcm_clk->init_data);
		break;
	default:
		break;
	}
	bcm_clk->u.data = NULL;
	bcm_clk->type = bcm_clk_none;
}