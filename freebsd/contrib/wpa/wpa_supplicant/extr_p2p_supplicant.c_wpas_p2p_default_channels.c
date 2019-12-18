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
struct wpa_supplicant {TYPE_1__* global; } ;
struct p2p_channels {int reg_classes; TYPE_2__* reg_class; } ;
struct TYPE_4__ {int reg_class; scalar_t__ channels; } ;
struct TYPE_3__ {int p2p_24ghz_social_channels; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  os_memset (struct p2p_channels*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpas_p2p_add_chan (TYPE_2__*,int) ; 
 int /*<<< orphan*/  wpas_p2p_disallowed_freq (TYPE_1__*,int) ; 

__attribute__((used)) static int wpas_p2p_default_channels(struct wpa_supplicant *wpa_s,
				     struct p2p_channels *chan,
				     struct p2p_channels *cli_chan)
{
	int i, cla = 0;

	wpa_s->global->p2p_24ghz_social_channels = 1;

	os_memset(cli_chan, 0, sizeof(*cli_chan));

	wpa_printf(MSG_DEBUG, "P2P: Enable operating classes for 2.4 GHz "
		   "band");

	/* Operating class 81 - 2.4 GHz band channels 1..13 */
	chan->reg_class[cla].reg_class = 81;
	chan->reg_class[cla].channels = 0;
	for (i = 0; i < 11; i++) {
		if (!wpas_p2p_disallowed_freq(wpa_s->global, 2412 + i * 5))
			wpas_p2p_add_chan(&chan->reg_class[cla], i + 1);
	}
	if (chan->reg_class[cla].channels)
		cla++;

	wpa_printf(MSG_DEBUG, "P2P: Enable operating classes for lower 5 GHz "
		   "band");

	/* Operating class 115 - 5 GHz, channels 36-48 */
	chan->reg_class[cla].reg_class = 115;
	chan->reg_class[cla].channels = 0;
	if (!wpas_p2p_disallowed_freq(wpa_s->global, 5000 + 36 * 5))
		wpas_p2p_add_chan(&chan->reg_class[cla], 36);
	if (!wpas_p2p_disallowed_freq(wpa_s->global, 5000 + 40 * 5))
		wpas_p2p_add_chan(&chan->reg_class[cla], 40);
	if (!wpas_p2p_disallowed_freq(wpa_s->global, 5000 + 44 * 5))
		wpas_p2p_add_chan(&chan->reg_class[cla], 44);
	if (!wpas_p2p_disallowed_freq(wpa_s->global, 5000 + 48 * 5))
		wpas_p2p_add_chan(&chan->reg_class[cla], 48);
	if (chan->reg_class[cla].channels)
		cla++;

	wpa_printf(MSG_DEBUG, "P2P: Enable operating classes for higher 5 GHz "
		   "band");

	/* Operating class 124 - 5 GHz, channels 149,153,157,161 */
	chan->reg_class[cla].reg_class = 124;
	chan->reg_class[cla].channels = 0;
	if (!wpas_p2p_disallowed_freq(wpa_s->global, 5000 + 149 * 5))
		wpas_p2p_add_chan(&chan->reg_class[cla], 149);
	if (!wpas_p2p_disallowed_freq(wpa_s->global, 5000 + 153 * 5))
		wpas_p2p_add_chan(&chan->reg_class[cla], 153);
	if (!wpas_p2p_disallowed_freq(wpa_s->global, 5000 + 156 * 5))
		wpas_p2p_add_chan(&chan->reg_class[cla], 157);
	if (!wpas_p2p_disallowed_freq(wpa_s->global, 5000 + 161 * 5))
		wpas_p2p_add_chan(&chan->reg_class[cla], 161);
	if (chan->reg_class[cla].channels)
		cla++;

	chan->reg_classes = cla;
	return 0;
}