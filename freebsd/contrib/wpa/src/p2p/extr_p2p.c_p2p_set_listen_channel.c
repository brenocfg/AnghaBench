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
typedef  scalar_t__ u8 ;
struct p2p_data {scalar_t__ state; scalar_t__ pending_channel_forced; scalar_t__ pending_channel; scalar_t__ pending_reg_class; TYPE_1__* cfg; } ;
struct TYPE_2__ {scalar_t__ channel_forced; scalar_t__ channel; scalar_t__ reg_class; } ;

/* Variables and functions */
 scalar_t__ P2P_IDLE ; 
 scalar_t__ p2p_channel_to_freq (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  p2p_dbg (struct p2p_data*,char*,...) ; 

int p2p_set_listen_channel(struct p2p_data *p2p, u8 reg_class, u8 channel,
			   u8 forced)
{
	if (p2p_channel_to_freq(reg_class, channel) < 0)
		return -1;

	/*
	 * Listen channel was set in configuration or set by control interface;
	 * cannot override it.
	 */
	if (p2p->cfg->channel_forced && forced == 0) {
		p2p_dbg(p2p,
			"Listen channel was previously configured - do not override based on optimization");
		return -1;
	}

	p2p_dbg(p2p, "Set Listen channel: reg_class %u channel %u",
		reg_class, channel);

	if (p2p->state == P2P_IDLE) {
		p2p->cfg->reg_class = reg_class;
		p2p->cfg->channel = channel;
		p2p->cfg->channel_forced = forced;
	} else {
		p2p_dbg(p2p, "Defer setting listen channel");
		p2p->pending_reg_class = reg_class;
		p2p->pending_channel = channel;
		p2p->pending_channel_forced = forced;
	}

	return 0;
}