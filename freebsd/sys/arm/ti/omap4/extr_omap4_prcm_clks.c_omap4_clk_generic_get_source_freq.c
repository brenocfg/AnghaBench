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
struct ti_clock_dev {int /*<<< orphan*/  id; } ;
struct omap4_clk_details {scalar_t__ src_freq; } ;

/* Variables and functions */
 int ENXIO ; 
 struct omap4_clk_details* omap4_clk_details (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
omap4_clk_generic_get_source_freq(struct ti_clock_dev *clkdev,
                                  unsigned int *freq
                                  )
{
	struct omap4_clk_details* clk_details = omap4_clk_details(clkdev->id);

	if (clk_details == NULL)
		return (ENXIO);
	
	/* Simply return the stored frequency */
	if (freq)
		*freq = (unsigned int)clk_details->src_freq;
	
	return (0);
}