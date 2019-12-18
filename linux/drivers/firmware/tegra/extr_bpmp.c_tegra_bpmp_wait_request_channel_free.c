#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct tegra_bpmp_channel {TYPE_4__* bpmp; } ;
typedef  int /*<<< orphan*/  ktime_t ;
struct TYPE_8__ {TYPE_3__* soc; } ;
struct TYPE_5__ {unsigned long timeout; } ;
struct TYPE_6__ {TYPE_1__ cpu_tx; } ;
struct TYPE_7__ {TYPE_2__ channels; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 unsigned long ktime_us_delta (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_clock () ; 
 int /*<<< orphan*/  ns_to_ktime (int /*<<< orphan*/ ) ; 
 scalar_t__ tegra_bpmp_is_request_channel_free (struct tegra_bpmp_channel*) ; 

__attribute__((used)) static int
tegra_bpmp_wait_request_channel_free(struct tegra_bpmp_channel *channel)
{
	unsigned long timeout = channel->bpmp->soc->channels.cpu_tx.timeout;
	ktime_t start, now;

	start = ns_to_ktime(local_clock());

	do {
		if (tegra_bpmp_is_request_channel_free(channel))
			return 0;

		now = ns_to_ktime(local_clock());
	} while (ktime_us_delta(now, start) < timeout);

	return -ETIMEDOUT;
}