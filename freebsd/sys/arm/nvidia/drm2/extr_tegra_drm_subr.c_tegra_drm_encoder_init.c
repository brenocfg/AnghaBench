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
struct tegra_drm_encoder {scalar_t__ panel; } ;
struct tegra_drm {int dummy; } ;

/* Variables and functions */

int tegra_drm_encoder_init(struct tegra_drm_encoder *output,
    struct tegra_drm *drm)
{

	if (output->panel) {
		/* attach panel */
	}
	return (0);
}