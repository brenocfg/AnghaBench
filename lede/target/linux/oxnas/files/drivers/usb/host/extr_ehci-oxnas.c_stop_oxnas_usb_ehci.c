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
struct oxnas_hcd {int /*<<< orphan*/  clk; int /*<<< orphan*/  refsrc; int /*<<< orphan*/  phyref; scalar_t__ use_pllb; int /*<<< orphan*/  rst_phyb; int /*<<< orphan*/  rst_phya; int /*<<< orphan*/  rst_host; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stop_oxnas_usb_ehci(struct oxnas_hcd *oxnas)
{
	reset_control_assert(oxnas->rst_host);
	reset_control_assert(oxnas->rst_phya);
	reset_control_assert(oxnas->rst_phyb);

	if (oxnas->use_pllb) {
		clk_disable_unprepare(oxnas->phyref);
		clk_disable_unprepare(oxnas->refsrc);
	}
	clk_disable_unprepare(oxnas->clk);
}