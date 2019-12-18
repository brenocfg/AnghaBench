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
struct TYPE_2__ {unsigned int count; } ;
struct tegra_bpmp {int /*<<< orphan*/ * threaded_channels; TYPE_1__ threaded; int /*<<< orphan*/ * rx_channel; int /*<<< orphan*/ * tx_channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  tegra186_bpmp_channel_reset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tegra186_bpmp_resume(struct tegra_bpmp *bpmp)
{
	unsigned int i;

	/* reset message channels */
	tegra186_bpmp_channel_reset(bpmp->tx_channel);
	tegra186_bpmp_channel_reset(bpmp->rx_channel);

	for (i = 0; i < bpmp->threaded.count; i++)
		tegra186_bpmp_channel_reset(&bpmp->threaded_channels[i]);

	return 0;
}