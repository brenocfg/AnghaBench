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
struct tegra_bpmp_channel {int /*<<< orphan*/  completion; TYPE_1__* ob; } ;
struct TYPE_2__ {unsigned long flags; } ;

/* Variables and functions */
 unsigned long MSG_RING ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tegra_bpmp_channel_signal(struct tegra_bpmp_channel *channel)
{
	unsigned long flags = channel->ob->flags;

	if ((flags & MSG_RING) == 0)
		return;

	complete(&channel->completion);
}