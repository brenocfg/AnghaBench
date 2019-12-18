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
struct tegra_bpmp_ops {int dummy; } ;
struct tegra_bpmp_channel {struct tegra_bpmp* bpmp; } ;
struct tegra_bpmp {TYPE_1__* soc; } ;
struct TYPE_2__ {struct tegra_bpmp_ops const* ops; } ;

/* Variables and functions */

__attribute__((used)) static inline const struct tegra_bpmp_ops *
channel_to_ops(struct tegra_bpmp_channel *channel)
{
	struct tegra_bpmp *bpmp = channel->bpmp;

	return bpmp->soc->ops;
}