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
typedef  scalar_t__ u8 ;
struct TYPE_4__ {int /*<<< orphan*/  num_modes; int /*<<< orphan*/ * modes; } ;
struct wpa_supplicant {TYPE_3__* conf; TYPE_2__* global; TYPE_1__ hw; } ;
struct p2p_reg_class {size_t channels; scalar_t__* channel; scalar_t__ reg_class; } ;
struct p2p_channels {int reg_classes; struct p2p_reg_class* reg_class; } ;
struct oper_class_map {scalar_t__ p2p; scalar_t__ min_chan; scalar_t__ max_chan; scalar_t__ inc; scalar_t__ op_class; int /*<<< orphan*/  bw; int /*<<< orphan*/  mode; } ;
struct hostapd_hw_modes {scalar_t__ mode; } ;
typedef  enum chan_allowed { ____Placeholder_chan_allowed } chan_allowed ;
struct TYPE_6__ {scalar_t__ p2p_add_cli_chan; } ;
struct TYPE_5__ {int p2p_24ghz_social_channels; } ;

/* Variables and functions */
 int ALLOWED ; 
 scalar_t__ HOSTAPD_MODE_IEEE80211G ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int NO_IR ; 
 scalar_t__ NO_P2P_SUPP ; 
 struct hostapd_hw_modes* get_mode (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct oper_class_map* global_op_class ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,scalar_t__*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int wpas_p2p_default_channels (struct wpa_supplicant*,struct p2p_channels*,struct p2p_channels*) ; 
 int wpas_p2p_verify_channel (struct wpa_supplicant*,struct hostapd_hw_modes*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wpas_p2p_setup_channels(struct wpa_supplicant *wpa_s,
				   struct p2p_channels *chan,
				   struct p2p_channels *cli_chan)
{
	struct hostapd_hw_modes *mode;
	int cla, op, cli_cla;

	if (wpa_s->hw.modes == NULL) {
		wpa_printf(MSG_DEBUG, "P2P: Driver did not support fetching "
			   "of all supported channels; assume dualband "
			   "support");
		return wpas_p2p_default_channels(wpa_s, chan, cli_chan);
	}

	cla = cli_cla = 0;

	for (op = 0; global_op_class[op].op_class; op++) {
		const struct oper_class_map *o = &global_op_class[op];
		u8 ch;
		struct p2p_reg_class *reg = NULL, *cli_reg = NULL;

		if (o->p2p == NO_P2P_SUPP)
			continue;

		mode = get_mode(wpa_s->hw.modes, wpa_s->hw.num_modes, o->mode);
		if (mode == NULL)
			continue;
		if (mode->mode == HOSTAPD_MODE_IEEE80211G)
			wpa_s->global->p2p_24ghz_social_channels = 1;
		for (ch = o->min_chan; ch <= o->max_chan; ch += o->inc) {
			enum chan_allowed res;
			res = wpas_p2p_verify_channel(wpa_s, mode, ch, o->bw);
			if (res == ALLOWED) {
				if (reg == NULL) {
					wpa_printf(MSG_DEBUG, "P2P: Add operating class %u",
						   o->op_class);
					reg = &chan->reg_class[cla];
					cla++;
					reg->reg_class = o->op_class;
				}
				reg->channel[reg->channels] = ch;
				reg->channels++;
			} else if (res == NO_IR &&
				   wpa_s->conf->p2p_add_cli_chan) {
				if (cli_reg == NULL) {
					wpa_printf(MSG_DEBUG, "P2P: Add operating class %u (client only)",
						   o->op_class);
					cli_reg = &cli_chan->reg_class[cli_cla];
					cli_cla++;
					cli_reg->reg_class = o->op_class;
				}
				cli_reg->channel[cli_reg->channels] = ch;
				cli_reg->channels++;
			}
		}
		if (reg) {
			wpa_hexdump(MSG_DEBUG, "P2P: Channels",
				    reg->channel, reg->channels);
		}
		if (cli_reg) {
			wpa_hexdump(MSG_DEBUG, "P2P: Channels (client only)",
				    cli_reg->channel, cli_reg->channels);
		}
	}

	chan->reg_classes = cla;
	cli_chan->reg_classes = cli_cla;

	return 0;
}