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
struct wpa_freq_range_list {int dummy; } ;
struct p2p_reg_class {size_t channels; struct p2p_reg_class* channel; int /*<<< orphan*/  reg_class; } ;
struct p2p_channels {size_t reg_classes; struct p2p_reg_class* reg_class; } ;

/* Variables and functions */
 scalar_t__ freq_range_list_includes (struct wpa_freq_range_list const*,int) ; 
 int /*<<< orphan*/  os_memmove (struct p2p_reg_class*,struct p2p_reg_class*,size_t) ; 
 int p2p_channel_to_freq (int /*<<< orphan*/ ,struct p2p_reg_class) ; 

void p2p_channels_remove_freqs(struct p2p_channels *chan,
			       const struct wpa_freq_range_list *list)
{
	size_t o, c;

	if (list == NULL)
		return;

	o = 0;
	while (o < chan->reg_classes) {
		struct p2p_reg_class *op = &chan->reg_class[o];

		c = 0;
		while (c < op->channels) {
			int freq = p2p_channel_to_freq(op->reg_class,
						       op->channel[c]);
			if (freq > 0 && freq_range_list_includes(list, freq)) {
				op->channels--;
				os_memmove(&op->channel[c],
					   &op->channel[c + 1],
					   op->channels - c);
			} else
				c++;
		}

		if (op->channels == 0) {
			chan->reg_classes--;
			os_memmove(&chan->reg_class[o], &chan->reg_class[o + 1],
				   (chan->reg_classes - o) *
				   sizeof(struct p2p_reg_class));
		} else
			o++;
	}
}