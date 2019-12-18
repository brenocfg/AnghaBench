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
struct p2p_data {TYPE_1__* cfg; } ;
struct p2p_channels {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  cli_channels; int /*<<< orphan*/  channels; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,struct p2p_channels const*,int) ; 
 int /*<<< orphan*/  p2p_channels_dump (struct p2p_data*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p2p_dbg (struct p2p_data*,char*) ; 

void p2p_update_channel_list(struct p2p_data *p2p,
			     const struct p2p_channels *chan,
			     const struct p2p_channels *cli_chan)
{
	p2p_dbg(p2p, "Update channel list");
	os_memcpy(&p2p->cfg->channels, chan, sizeof(struct p2p_channels));
	p2p_channels_dump(p2p, "channels", &p2p->cfg->channels);
	os_memcpy(&p2p->cfg->cli_channels, cli_chan,
		  sizeof(struct p2p_channels));
	p2p_channels_dump(p2p, "cli_channels", &p2p->cfg->cli_channels);
}