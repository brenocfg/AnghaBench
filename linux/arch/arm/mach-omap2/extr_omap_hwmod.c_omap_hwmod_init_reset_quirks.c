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
struct ti_sysc_module_data {int dummy; } ;
struct omap_hwmod {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dra7_reset_quirks ; 
 int /*<<< orphan*/  omap24xx_reset_quirks ; 
 int /*<<< orphan*/  omap_hwmod_init_reset_quirk (struct device*,struct omap_hwmod*,struct ti_sysc_module_data const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_reset_quirks ; 
 scalar_t__ soc_is_dra7xx () ; 
 scalar_t__ soc_is_omap24xx () ; 

__attribute__((used)) static void
omap_hwmod_init_reset_quirks(struct device *dev, struct omap_hwmod *oh,
			     const struct ti_sysc_module_data *data)
{
	if (soc_is_omap24xx())
		omap_hwmod_init_reset_quirk(dev, oh, data,
					    omap24xx_reset_quirks,
					    ARRAY_SIZE(omap24xx_reset_quirks));

	if (soc_is_dra7xx())
		omap_hwmod_init_reset_quirk(dev, oh, data, dra7_reset_quirks,
					    ARRAY_SIZE(dra7_reset_quirks));

	omap_hwmod_init_reset_quirk(dev, oh, data, omap_reset_quirks,
				    ARRAY_SIZE(omap_reset_quirks));
}