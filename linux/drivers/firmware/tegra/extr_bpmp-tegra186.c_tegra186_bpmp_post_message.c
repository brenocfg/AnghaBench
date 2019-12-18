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
 int tegra_ivc_write_advance (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tegra186_bpmp_post_message(struct tegra_bpmp_channel *channel)
{
	return tegra_ivc_write_advance(channel->ivc);
}