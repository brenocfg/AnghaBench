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
struct hyperv_guid {int dummy; } ;
struct vmbus_channel {struct hyperv_guid const ch_guid_inst; } ;

/* Variables and functions */

const struct hyperv_guid *
vmbus_chan_guid_inst(const struct vmbus_channel *chan)
{
	return &chan->ch_guid_inst;
}