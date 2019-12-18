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
struct wpa_used_freq_data {int dummy; } ;
struct wpa_supplicant {unsigned int num_multichan_concurrent; TYPE_1__* global; } ;
struct p2p_channels {int dummy; } ;
typedef  enum wpas_p2p_channel_update_trig { ____Placeholder_wpas_p2p_channel_update_trig } wpas_p2p_channel_update_trig ;
typedef  int /*<<< orphan*/  cli_chan ;
typedef  int /*<<< orphan*/  chan ;
struct TYPE_2__ {int /*<<< orphan*/ * p2p; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_ERROR ; 
 unsigned int get_shared_radio_freqs_data (struct wpa_supplicant*,struct wpa_used_freq_data*,unsigned int) ; 
 struct wpa_used_freq_data* os_calloc (unsigned int,int) ; 
 int /*<<< orphan*/  os_free (struct wpa_used_freq_data*) ; 
 int /*<<< orphan*/  os_memset (struct p2p_channels*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  p2p_update_channel_list (int /*<<< orphan*/ *,struct p2p_channels*,struct p2p_channels*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpas_p2p_consider_moving_gos (struct wpa_supplicant*,struct wpa_used_freq_data*,unsigned int,int) ; 
 int /*<<< orphan*/  wpas_p2p_optimize_listen_channel (struct wpa_supplicant*,struct wpa_used_freq_data*,unsigned int) ; 
 scalar_t__ wpas_p2p_setup_channels (struct wpa_supplicant*,struct p2p_channels*,struct p2p_channels*) ; 

void wpas_p2p_update_channel_list(struct wpa_supplicant *wpa_s,
				  enum wpas_p2p_channel_update_trig trig)
{
	struct p2p_channels chan, cli_chan;
	struct wpa_used_freq_data *freqs = NULL;
	unsigned int num = wpa_s->num_multichan_concurrent;

	if (wpa_s->global == NULL || wpa_s->global->p2p == NULL)
		return;

	freqs = os_calloc(num, sizeof(struct wpa_used_freq_data));
	if (!freqs)
		return;

	num = get_shared_radio_freqs_data(wpa_s, freqs, num);

	os_memset(&chan, 0, sizeof(chan));
	os_memset(&cli_chan, 0, sizeof(cli_chan));
	if (wpas_p2p_setup_channels(wpa_s, &chan, &cli_chan)) {
		wpa_printf(MSG_ERROR, "P2P: Failed to update supported "
			   "channel list");
		return;
	}

	p2p_update_channel_list(wpa_s->global->p2p, &chan, &cli_chan);

	wpas_p2p_optimize_listen_channel(wpa_s, freqs, num);

	/*
	 * The used frequencies map changed, so it is possible that a GO is
	 * using a channel that is no longer valid for P2P use. It is also
	 * possible that due to policy consideration, it would be preferable to
	 * move it to a frequency already used by other station interfaces.
	 */
	wpas_p2p_consider_moving_gos(wpa_s, freqs, num, trig);

	os_free(freqs);
}