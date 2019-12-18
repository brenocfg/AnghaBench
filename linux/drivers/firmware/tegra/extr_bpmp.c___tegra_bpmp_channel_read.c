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
struct tegra_bpmp_channel {TYPE_1__* ib; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int code; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,size_t) ; 
 int tegra_bpmp_ack_response (struct tegra_bpmp_channel*) ; 

__attribute__((used)) static ssize_t __tegra_bpmp_channel_read(struct tegra_bpmp_channel *channel,
					 void *data, size_t size, int *ret)
{
	int err;

	if (data && size > 0)
		memcpy(data, channel->ib->data, size);

	err = tegra_bpmp_ack_response(channel);
	if (err < 0)
		return err;

	*ret = channel->ib->code;

	return 0;
}