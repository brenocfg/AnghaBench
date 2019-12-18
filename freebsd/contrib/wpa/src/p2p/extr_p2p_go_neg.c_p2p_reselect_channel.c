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
typedef  void* u8 ;
struct p2p_reg_class {void* reg_class; void** channel; } ;
struct p2p_data {scalar_t__ own_freq_preference; void* op_reg_class; void* op_channel; scalar_t__ best_freq_overall; scalar_t__ best_freq_5; scalar_t__ best_freq_24; TYPE_2__* cfg; } ;
struct p2p_channels {struct p2p_reg_class* reg_class; } ;
struct TYPE_4__ {unsigned int num_pref_chan; TYPE_1__* pref_chan; } ;
struct TYPE_3__ {void* op_class; void* chan; } ;

/* Variables and functions */
 scalar_t__ p2p_channel_select (struct p2p_channels*,int const*,void**,void**) ; 
 int p2p_channel_to_freq (void*,void*) ; 
 scalar_t__ p2p_channels_includes (struct p2p_channels*,void*,void*) ; 
 int /*<<< orphan*/  p2p_dbg (struct p2p_data*,char*,void*,void*) ; 
 scalar_t__ p2p_freq_to_channel (scalar_t__,void**,void**) ; 

void p2p_reselect_channel(struct p2p_data *p2p,
			  struct p2p_channels *intersection)
{
	struct p2p_reg_class *cl;
	int freq;
	u8 op_reg_class, op_channel;
	unsigned int i;
	const int op_classes_5ghz[] = { 124, 125, 115, 0 };
	const int op_classes_ht40[] = { 126, 127, 116, 117, 0 };
	const int op_classes_vht[] = { 128, 129, 130, 0 };

	if (p2p->own_freq_preference > 0 &&
	    p2p_freq_to_channel(p2p->own_freq_preference,
				&op_reg_class, &op_channel) == 0 &&
	    p2p_channels_includes(intersection, op_reg_class, op_channel)) {
		p2p_dbg(p2p, "Pick own channel preference (reg_class %u channel %u) from intersection",
			op_reg_class, op_channel);
		p2p->op_reg_class = op_reg_class;
		p2p->op_channel = op_channel;
		return;
	}

	if (p2p->best_freq_overall > 0 &&
	    p2p_freq_to_channel(p2p->best_freq_overall,
				&op_reg_class, &op_channel) == 0 &&
	    p2p_channels_includes(intersection, op_reg_class, op_channel)) {
		p2p_dbg(p2p, "Pick best overall channel (reg_class %u channel %u) from intersection",
			op_reg_class, op_channel);
		p2p->op_reg_class = op_reg_class;
		p2p->op_channel = op_channel;
		return;
	}

	/* First, try to pick the best channel from another band */
	freq = p2p_channel_to_freq(p2p->op_reg_class, p2p->op_channel);
	if (freq >= 2400 && freq < 2500 && p2p->best_freq_5 > 0 &&
	    !p2p_channels_includes(intersection, p2p->op_reg_class,
				   p2p->op_channel) &&
	    p2p_freq_to_channel(p2p->best_freq_5,
				&op_reg_class, &op_channel) == 0 &&
	    p2p_channels_includes(intersection, op_reg_class, op_channel)) {
		p2p_dbg(p2p, "Pick best 5 GHz channel (reg_class %u channel %u) from intersection",
			op_reg_class, op_channel);
		p2p->op_reg_class = op_reg_class;
		p2p->op_channel = op_channel;
		return;
	}

	if (freq >= 4900 && freq < 6000 && p2p->best_freq_24 > 0 &&
	    !p2p_channels_includes(intersection, p2p->op_reg_class,
				   p2p->op_channel) &&
	    p2p_freq_to_channel(p2p->best_freq_24,
				&op_reg_class, &op_channel) == 0 &&
	    p2p_channels_includes(intersection, op_reg_class, op_channel)) {
		p2p_dbg(p2p, "Pick best 2.4 GHz channel (reg_class %u channel %u) from intersection",
			op_reg_class, op_channel);
		p2p->op_reg_class = op_reg_class;
		p2p->op_channel = op_channel;
		return;
	}

	/* Select channel with highest preference if the peer supports it */
	for (i = 0; p2p->cfg->pref_chan && i < p2p->cfg->num_pref_chan; i++) {
		if (p2p_channels_includes(intersection,
					  p2p->cfg->pref_chan[i].op_class,
					  p2p->cfg->pref_chan[i].chan)) {
			p2p->op_reg_class = p2p->cfg->pref_chan[i].op_class;
			p2p->op_channel = p2p->cfg->pref_chan[i].chan;
			p2p_dbg(p2p, "Pick highest preferred channel (op_class %u channel %u) from intersection",
				p2p->op_reg_class, p2p->op_channel);
			return;
		}
	}

	/* Try a channel where we might be able to use VHT */
	if (p2p_channel_select(intersection, op_classes_vht,
			       &p2p->op_reg_class, &p2p->op_channel) == 0) {
		p2p_dbg(p2p, "Pick possible VHT channel (op_class %u channel %u) from intersection",
			p2p->op_reg_class, p2p->op_channel);
		return;
	}

	/* Try a channel where we might be able to use HT40 */
	if (p2p_channel_select(intersection, op_classes_ht40,
			       &p2p->op_reg_class, &p2p->op_channel) == 0) {
		p2p_dbg(p2p, "Pick possible HT40 channel (op_class %u channel %u) from intersection",
			p2p->op_reg_class, p2p->op_channel);
		return;
	}

	/* Prefer a 5 GHz channel */
	if (p2p_channel_select(intersection, op_classes_5ghz,
			       &p2p->op_reg_class, &p2p->op_channel) == 0) {
		p2p_dbg(p2p, "Pick possible 5 GHz channel (op_class %u channel %u) from intersection",
			p2p->op_reg_class, p2p->op_channel);
		return;
	}

	/*
	 * Try to see if the original channel is in the intersection. If
	 * so, no need to change anything, as it already contains some
	 * randomness.
	 */
	if (p2p_channels_includes(intersection, p2p->op_reg_class,
				  p2p->op_channel)) {
		p2p_dbg(p2p, "Using original operating class and channel (op_class %u channel %u) from intersection",
			p2p->op_reg_class, p2p->op_channel);
		return;
	}

	/*
	 * Fall back to whatever is included in the channel intersection since
	 * no better options seems to be available.
	 */
	cl = &intersection->reg_class[0];
	p2p_dbg(p2p, "Pick another channel (reg_class %u channel %u) from intersection",
		cl->reg_class, cl->channel[0]);
	p2p->op_reg_class = cl->reg_class;
	p2p->op_channel = cl->channel[0];
}