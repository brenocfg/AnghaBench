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
struct device_node {int /*<<< orphan*/  name; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct clk*) ; 
 unsigned long abs (unsigned int) ; 
 unsigned long clk_get_rate (struct clk*) ; 
 struct clk* clk_get_sys (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ clk_prepare_enable (struct clk*) ; 
 int /*<<< orphan*/  clk_set_rate (struct clk*,unsigned int) ; 
 struct clk* of_clk_get (struct device_node*,int /*<<< orphan*/ ) ; 
 struct device_node* of_find_compatible_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned int,...) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

__attribute__((used)) static void mpc512x_set_pixel_clock(unsigned int pixclock)
{
	struct device_node *np;
	struct clk *clk_diu;
	unsigned long epsilon, minpixclock, maxpixclock;
	unsigned long offset, want, got, delta;

	/* lookup and enable the DIU clock */
	np = of_find_compatible_node(NULL, NULL, "fsl,mpc5121-diu");
	if (!np) {
		pr_err("Could not find DIU device tree node.\n");
		return;
	}
	clk_diu = of_clk_get(np, 0);
	if (IS_ERR(clk_diu)) {
		/* backwards compat with device trees that lack clock specs */
		clk_diu = clk_get_sys(np->name, "ipg");
	}
	of_node_put(np);
	if (IS_ERR(clk_diu)) {
		pr_err("Could not lookup DIU clock.\n");
		return;
	}
	if (clk_prepare_enable(clk_diu)) {
		pr_err("Could not enable DIU clock.\n");
		return;
	}

	/*
	 * convert the picoseconds spec into the desired clock rate,
	 * determine the acceptable clock range for the monitor (+/- 5%),
	 * do the calculation in steps to avoid integer overflow
	 */
	pr_debug("DIU pixclock in ps - %u\n", pixclock);
	pixclock = (1000000000 / pixclock) * 1000;
	pr_debug("DIU pixclock freq  - %u\n", pixclock);
	epsilon = pixclock / 20; /* pixclock * 0.05 */
	pr_debug("DIU deviation      - %lu\n", epsilon);
	minpixclock = pixclock - epsilon;
	maxpixclock = pixclock + epsilon;
	pr_debug("DIU minpixclock    - %lu\n", minpixclock);
	pr_debug("DIU maxpixclock    - %lu\n", maxpixclock);

	/*
	 * check whether the DIU supports the desired pixel clock
	 *
	 * - simply request the desired clock and see what the
	 *   platform's clock driver will make of it, assuming that it
	 *   will setup the best approximation of the requested value
	 * - try other candidate frequencies in the order of decreasing
	 *   preference (i.e. with increasing distance from the desired
	 *   pixel clock, and checking the lower frequency before the
	 *   higher frequency to not overload the hardware) until the
	 *   first match is found -- any potential subsequent match
	 *   would only be as good as the former match or typically
	 *   would be less preferrable
	 *
	 * the offset increment of pixelclock divided by 64 is an
	 * arbitrary choice -- it's simple to calculate, in the typical
	 * case we expect the first check to succeed already, in the
	 * worst case seven frequencies get tested (the exact center and
	 * three more values each to the left and to the right) before
	 * the 5% tolerance window is exceeded, resulting in fast enough
	 * execution yet high enough probability of finding a suitable
	 * value, while the error rate will be in the order of single
	 * percents
	 */
	for (offset = 0; offset <= epsilon; offset += pixclock / 64) {
		want = pixclock - offset;
		pr_debug("DIU checking clock - %lu\n", want);
		clk_set_rate(clk_diu, want);
		got = clk_get_rate(clk_diu);
		delta = abs(pixclock - got);
		if (delta < epsilon)
			break;
		if (!offset)
			continue;
		want = pixclock + offset;
		pr_debug("DIU checking clock - %lu\n", want);
		clk_set_rate(clk_diu, want);
		got = clk_get_rate(clk_diu);
		delta = abs(pixclock - got);
		if (delta < epsilon)
			break;
	}
	if (offset <= epsilon) {
		pr_debug("DIU clock accepted - %lu\n", want);
		pr_debug("DIU pixclock want %u, got %lu, delta %lu, eps %lu\n",
			 pixclock, got, delta, epsilon);
		return;
	}
	pr_warn("DIU pixclock auto search unsuccessful\n");

	/*
	 * what is the most appropriate action to take when the search
	 * for an available pixel clock which is acceptable to the
	 * monitor has failed?  disable the DIU (clock) or just provide
	 * a "best effort"?  we go with the latter
	 */
	pr_warn("DIU pixclock best effort fallback (backend's choice)\n");
	clk_set_rate(clk_diu, pixclock);
	got = clk_get_rate(clk_diu);
	delta = abs(pixclock - got);
	pr_debug("DIU pixclock want %u, got %lu, delta %lu, eps %lu\n",
		 pixclock, got, delta, epsilon);
}