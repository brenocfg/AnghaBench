#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u8 ;
struct TYPE_6__ {int reg_classes; TYPE_1__* reg_class; } ;
struct p2p_data {unsigned int op_reg_class; unsigned int op_channel; TYPE_2__* cfg; TYPE_3__ channels; } ;
struct p2p_channels {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  channels; int /*<<< orphan*/  cli_channels; } ;
struct TYPE_4__ {int channels; unsigned int reg_class; unsigned int* channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_memcpy (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  p2p_channels_includes (int /*<<< orphan*/ *,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  p2p_dbg (struct p2p_data*,char*,unsigned int,...) ; 
 scalar_t__ p2p_freq_to_channel (unsigned int,unsigned int*,unsigned int*) ; 

__attribute__((used)) static int p2p_prepare_channel_pref(struct p2p_data *p2p,
				    unsigned int force_freq,
				    unsigned int pref_freq, int go)
{
	u8 op_class, op_channel;
	unsigned int freq = force_freq ? force_freq : pref_freq;

	p2p_dbg(p2p, "Prepare channel pref - force_freq=%u pref_freq=%u go=%d",
		force_freq, pref_freq, go);
	if (p2p_freq_to_channel(freq, &op_class, &op_channel) < 0) {
		p2p_dbg(p2p, "Unsupported frequency %u MHz", freq);
		return -1;
	}

	if (!p2p_channels_includes(&p2p->cfg->channels, op_class, op_channel) &&
	    (go || !p2p_channels_includes(&p2p->cfg->cli_channels, op_class,
					  op_channel))) {
		p2p_dbg(p2p, "Frequency %u MHz (oper_class %u channel %u) not allowed for P2P",
			freq, op_class, op_channel);
		return -1;
	}

	p2p->op_reg_class = op_class;
	p2p->op_channel = op_channel;

	if (force_freq) {
		p2p->channels.reg_classes = 1;
		p2p->channels.reg_class[0].channels = 1;
		p2p->channels.reg_class[0].reg_class = p2p->op_reg_class;
		p2p->channels.reg_class[0].channel[0] = p2p->op_channel;
	} else {
		os_memcpy(&p2p->channels, &p2p->cfg->channels,
			  sizeof(struct p2p_channels));
	}

	return 0;
}