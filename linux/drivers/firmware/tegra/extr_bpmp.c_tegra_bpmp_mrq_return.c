#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tegra_bpmp_channel {TYPE_1__* ob; struct tegra_bpmp* bpmp; TYPE_2__* ib; } ;
struct tegra_bpmp {int dummy; } ;
struct TYPE_4__ {unsigned long flags; } ;
struct TYPE_3__ {int code; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 unsigned long MSG_ACK ; 
 size_t MSG_DATA_MIN_SZ ; 
 unsigned long MSG_RING ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,size_t) ; 
 int tegra_bpmp_ack_request (struct tegra_bpmp_channel*) ; 
 int /*<<< orphan*/  tegra_bpmp_is_response_channel_free (struct tegra_bpmp_channel*) ; 
 int tegra_bpmp_post_response (struct tegra_bpmp_channel*) ; 
 int tegra_bpmp_ring_doorbell (struct tegra_bpmp*) ; 

void tegra_bpmp_mrq_return(struct tegra_bpmp_channel *channel, int code,
			   const void *data, size_t size)
{
	unsigned long flags = channel->ib->flags;
	struct tegra_bpmp *bpmp = channel->bpmp;
	int err;

	if (WARN_ON(size > MSG_DATA_MIN_SZ))
		return;

	err = tegra_bpmp_ack_request(channel);
	if (WARN_ON(err < 0))
		return;

	if ((flags & MSG_ACK) == 0)
		return;

	if (WARN_ON(!tegra_bpmp_is_response_channel_free(channel)))
		return;

	channel->ob->code = code;

	if (data && size > 0)
		memcpy(channel->ob->data, data, size);

	err = tegra_bpmp_post_response(channel);
	if (WARN_ON(err < 0))
		return;

	if (flags & MSG_RING) {
		err = tegra_bpmp_ring_doorbell(bpmp);
		if (WARN_ON(err < 0))
			return;
	}
}