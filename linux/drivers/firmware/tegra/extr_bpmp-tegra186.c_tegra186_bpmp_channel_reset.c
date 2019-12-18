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
struct tegra_bpmp_channel {int /*<<< orphan*/  ivc; } ;

/* Variables and functions */
 scalar_t__ tegra_ivc_notified (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_ivc_reset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tegra186_bpmp_channel_reset(struct tegra_bpmp_channel *channel)
{
	/* reset the channel state */
	tegra_ivc_reset(channel->ivc);

	/* sync the channel state with BPMP */
	while (tegra_ivc_notified(channel->ivc))
		;
}