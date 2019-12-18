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
struct p2p_reg_class {size_t channels; void** channel; void* reg_class; } ;
struct p2p_data {void* last_prog_scan_chan; void* last_prog_scan_class; TYPE_1__* cfg; } ;
struct p2p_channels {size_t reg_classes; struct p2p_reg_class* reg_class; } ;
struct TYPE_2__ {struct p2p_channels channels; } ;

/* Variables and functions */
 int p2p_channel_to_freq (void*,void*) ; 
 int /*<<< orphan*/  p2p_dbg (struct p2p_data*,char*,void*,void*,int) ; 

__attribute__((used)) static int p2p_get_next_prog_freq(struct p2p_data *p2p)
{
	struct p2p_channels *c;
	struct p2p_reg_class *cla;
	size_t cl, ch;
	int found = 0;
	u8 reg_class;
	u8 channel;
	int freq;

	c = &p2p->cfg->channels;
	for (cl = 0; cl < c->reg_classes; cl++) {
		cla = &c->reg_class[cl];
		if (cla->reg_class != p2p->last_prog_scan_class)
			continue;
		for (ch = 0; ch < cla->channels; ch++) {
			if (cla->channel[ch] == p2p->last_prog_scan_chan) {
				found = 1;
				break;
			}
		}
		if (found)
			break;
	}

	if (!found) {
		/* Start from beginning */
		reg_class = c->reg_class[0].reg_class;
		channel = c->reg_class[0].channel[0];
	} else {
		/* Pick the next channel */
		ch++;
		if (ch == cla->channels) {
			cl++;
			if (cl == c->reg_classes)
				cl = 0;
			ch = 0;
		}
		reg_class = c->reg_class[cl].reg_class;
		channel = c->reg_class[cl].channel[ch];
	}

	freq = p2p_channel_to_freq(reg_class, channel);
	p2p_dbg(p2p, "Next progressive search channel: reg_class %u channel %u -> %d MHz",
		reg_class, channel, freq);
	p2p->last_prog_scan_class = reg_class;
	p2p->last_prog_scan_chan = channel;

	if (freq == 2412 || freq == 2437 || freq == 2462)
		return 0; /* No need to add social channels */
	return freq;
}