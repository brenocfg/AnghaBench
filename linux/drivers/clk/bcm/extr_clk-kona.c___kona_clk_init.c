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
struct kona_clk {int type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int __peri_clk_init (struct kona_clk*) ; 
#define  bcm_clk_peri 128 

__attribute__((used)) static bool __kona_clk_init(struct kona_clk *bcm_clk)
{
	switch (bcm_clk->type) {
	case bcm_clk_peri:
		return __peri_clk_init(bcm_clk);
	default:
		BUG();
	}
	return false;
}