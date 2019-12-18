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
struct tegra_bpmp_ops {int (* is_response_ready ) (struct tegra_bpmp_channel*) ;} ;
struct tegra_bpmp_channel {int dummy; } ;

/* Variables and functions */
 struct tegra_bpmp_ops* channel_to_ops (struct tegra_bpmp_channel*) ; 
 int stub1 (struct tegra_bpmp_channel*) ; 

__attribute__((used)) static bool tegra_bpmp_is_response_ready(struct tegra_bpmp_channel *channel)
{
	const struct tegra_bpmp_ops *ops = channel_to_ops(channel);

	return ops->is_response_ready(channel);
}