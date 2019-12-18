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
struct tegra_clk_frac_div {int /*<<< orphan*/  flags; int /*<<< orphan*/  frac_width; int /*<<< orphan*/  width; } ;

/* Variables and functions */
 int div_frac_get (unsigned long,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_div(struct tegra_clk_frac_div *divider, unsigned long rate,
		   unsigned long parent_rate)
{
	int div;

	div = div_frac_get(rate, parent_rate, divider->width,
			   divider->frac_width, divider->flags);

	if (div < 0)
		return 0;

	return div;
}