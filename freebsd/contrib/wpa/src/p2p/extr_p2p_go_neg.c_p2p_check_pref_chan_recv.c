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
typedef  void* u8 ;
struct p2p_message {int pref_freq_list_len; int /*<<< orphan*/ * pref_freq_list; } ;
struct p2p_device {int dummy; } ;
struct p2p_data {TYPE_1__* cfg; int /*<<< orphan*/  channels; void* op_channel; void* op_reg_class; } ;
struct p2p_channels {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  channels; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 unsigned int p2p_channel_to_freq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p2p_dbg (struct p2p_data*,char*,...) ; 
 scalar_t__ p2p_freq_to_channel (unsigned int,void**,void**) ; 

__attribute__((used)) static void p2p_check_pref_chan_recv(struct p2p_data *p2p, int go,
				     struct p2p_device *dev,
				     struct p2p_message *msg,
				     unsigned freq_list[], unsigned int size)
{
	u8 op_class, op_channel;
	unsigned int oper_freq = 0, i, j;
	int found = 0;

	/*
	 * Peer device supports a Preferred Frequency List.
	 * Search for a common channel in the preferred frequency lists
	 * of both peer and local devices.
	 */
	for (i = 0; i < size && !found; i++) {
		for (j = 2; j < (msg->pref_freq_list_len / 2); j++) {
			oper_freq = p2p_channel_to_freq(
				msg->pref_freq_list[2 * j],
				msg->pref_freq_list[2 * j + 1]);
			if (freq_list[i] != oper_freq)
				continue;
			if (p2p_freq_to_channel(oper_freq, &op_class,
						&op_channel) < 0)
				continue; /* cannot happen */
			p2p->op_reg_class = op_class;
			p2p->op_channel = op_channel;
			os_memcpy(&p2p->channels, &p2p->cfg->channels,
				  sizeof(struct p2p_channels));
			found = 1;
			break;
		}
	}

	if (found) {
		p2p_dbg(p2p,
			"Freq %d MHz is a common preferred channel for both peer and local, use it as operating channel",
			oper_freq);
	} else {
		p2p_dbg(p2p, "No common preferred channels found!");
	}
}