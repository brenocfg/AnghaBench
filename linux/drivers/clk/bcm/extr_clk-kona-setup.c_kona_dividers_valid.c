#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int frac_width; } ;
struct TYPE_5__ {TYPE_1__ s; } ;
struct bcm_clk_div {TYPE_2__ u; } ;
struct peri_clk_data {struct bcm_clk_div pre_div; struct bcm_clk_div div; } ;
struct TYPE_6__ {struct peri_clk_data* peri; } ;
struct kona_clk {scalar_t__ type; TYPE_3__ u; } ;

/* Variables and functions */
 int BITS_PER_BYTE ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ bcm_clk_peri ; 
 int /*<<< orphan*/  divider_exists (struct bcm_clk_div*) ; 
 scalar_t__ divider_is_fixed (struct bcm_clk_div*) ; 

__attribute__((used)) static bool kona_dividers_valid(struct kona_clk *bcm_clk)
{
	struct peri_clk_data *peri = bcm_clk->u.peri;
	struct bcm_clk_div *div;
	struct bcm_clk_div *pre_div;
	u32 limit;

	BUG_ON(bcm_clk->type != bcm_clk_peri);

	if (!divider_exists(&peri->div) || !divider_exists(&peri->pre_div))
		return true;

	div = &peri->div;
	pre_div = &peri->pre_div;
	if (divider_is_fixed(div) || divider_is_fixed(pre_div))
		return true;

	limit = BITS_PER_BYTE * sizeof(u32);

	return div->u.s.frac_width + pre_div->u.s.frac_width <= limit;
}