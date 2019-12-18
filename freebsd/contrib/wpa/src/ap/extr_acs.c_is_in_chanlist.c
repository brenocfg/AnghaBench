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
struct hostapd_iface {TYPE_1__* conf; } ;
struct hostapd_channel_data {int /*<<< orphan*/  chan; } ;
struct TYPE_4__ {int /*<<< orphan*/  num; } ;
struct TYPE_3__ {TYPE_2__ acs_ch_list; } ;

/* Variables and functions */
 int freq_range_list_includes (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int is_in_chanlist(struct hostapd_iface *iface,
			  struct hostapd_channel_data *chan)
{
	if (!iface->conf->acs_ch_list.num)
		return 1;

	return freq_range_list_includes(&iface->conf->acs_ch_list, chan->chan);
}