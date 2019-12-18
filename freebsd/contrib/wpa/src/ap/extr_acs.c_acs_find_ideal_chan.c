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
typedef  long double u32 ;
struct hostapd_iface {TYPE_1__* current_mode; TYPE_2__* conf; } ;
struct hostapd_channel_data {long double chan; long double interference_factor; long double freq; } ;
struct acs_bias {scalar_t__ channel; long double bias; } ;
struct TYPE_4__ {int secondary_channel; unsigned int num_acs_chan_bias; struct acs_bias* acs_chan_bias; scalar_t__ ieee80211ax; scalar_t__ ieee80211ac; scalar_t__ ieee80211n; } ;
struct TYPE_3__ {int num_channels; scalar_t__ mode; struct hostapd_channel_data* channels; } ;

/* Variables and functions */
 long double ACS_24GHZ_PREFER_1_6_11 ; 
 long double ACS_ADJ_WEIGHT ; 
 long double ACS_NEXT_ADJ_WEIGHT ; 
#define  CHANWIDTH_160MHZ 129 
#define  CHANWIDTH_80MHZ 128 
 scalar_t__ HOSTAPD_MODE_IEEE80211A ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 struct hostapd_channel_data* acs_find_chan (struct hostapd_iface*,long double) ; 
 scalar_t__ acs_usable_chan (struct hostapd_channel_data*) ; 
 int /*<<< orphan*/  acs_usable_ht40_chan (struct hostapd_channel_data*) ; 
 int /*<<< orphan*/  acs_usable_vht160_chan (struct hostapd_channel_data*) ; 
 int /*<<< orphan*/  acs_usable_vht80_chan (struct hostapd_channel_data*) ; 
 int /*<<< orphan*/  chan_bw_allowed (struct hostapd_channel_data*,long double,int,int) ; 
 int /*<<< orphan*/  chan_pri_allowed (struct hostapd_channel_data*) ; 
 int const hostapd_get_oper_chwidth (TYPE_2__*) ; 
 scalar_t__ is_24ghz_mode (scalar_t__) ; 
 scalar_t__ is_common_24ghz_chan (scalar_t__) ; 
 int /*<<< orphan*/  is_in_chanlist (struct hostapd_iface*,struct hostapd_channel_data*) ; 
 long double num_chan_to_bw (int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static struct hostapd_channel_data *
acs_find_ideal_chan(struct hostapd_iface *iface)
{
	struct hostapd_channel_data *chan, *adj_chan, *ideal_chan = NULL,
		*rand_chan = NULL;
	long double factor, ideal_factor = 0;
	int i, j;
	int n_chans = 1;
	u32 bw;
	unsigned int k;

	/* TODO: HT40- support */

	if (iface->conf->ieee80211n &&
	    iface->conf->secondary_channel == -1) {
		wpa_printf(MSG_ERROR, "ACS: HT40- is not supported yet. Please try HT40+");
		return NULL;
	}

	if (iface->conf->ieee80211n &&
	    iface->conf->secondary_channel)
		n_chans = 2;

	if (iface->conf->ieee80211ac || iface->conf->ieee80211ax) {
		switch (hostapd_get_oper_chwidth(iface->conf)) {
		case CHANWIDTH_80MHZ:
			n_chans = 4;
			break;
		case CHANWIDTH_160MHZ:
			n_chans = 8;
			break;
		}
	}

	bw = num_chan_to_bw(n_chans);

	/* TODO: VHT/HE80+80. Update acs_adjust_center_freq() too. */

	wpa_printf(MSG_DEBUG,
		   "ACS: Survey analysis for selected bandwidth %d MHz", bw);

	for (i = 0; i < iface->current_mode->num_channels; i++) {
		double total_weight;
		struct acs_bias *bias, tmp_bias;

		chan = &iface->current_mode->channels[i];

		/* Since in the current ACS implementation the first channel is
		 * always a primary channel, skip channels not available as
		 * primary until more sophisticated channel selection is
		 * implemented. */
		if (!chan_pri_allowed(chan))
			continue;

		if (!is_in_chanlist(iface, chan))
			continue;

		if (!chan_bw_allowed(chan, bw, 1, 1)) {
			wpa_printf(MSG_DEBUG,
				   "ACS: Channel %d: BW %u is not supported",
				   chan->chan, bw);
			continue;
		}

		/* HT40 on 5 GHz has a limited set of primary channels as per
		 * 11n Annex J */
		if (iface->current_mode->mode == HOSTAPD_MODE_IEEE80211A &&
		    iface->conf->ieee80211n &&
		    iface->conf->secondary_channel &&
		    !acs_usable_ht40_chan(chan)) {
			wpa_printf(MSG_DEBUG, "ACS: Channel %d: not allowed as primary channel for HT40",
				   chan->chan);
			continue;
		}

		if (iface->current_mode->mode == HOSTAPD_MODE_IEEE80211A &&
		    (iface->conf->ieee80211ac || iface->conf->ieee80211ax)) {
			if (hostapd_get_oper_chwidth(iface->conf) ==
			    CHANWIDTH_80MHZ &&
			    !acs_usable_vht80_chan(chan)) {
				wpa_printf(MSG_DEBUG,
					   "ACS: Channel %d: not allowed as primary channel for VHT80",
					   chan->chan);
				continue;
			}

			if (hostapd_get_oper_chwidth(iface->conf) ==
			    CHANWIDTH_160MHZ &&
			    !acs_usable_vht160_chan(chan)) {
				wpa_printf(MSG_DEBUG,
					   "ACS: Channel %d: not allowed as primary channel for VHT160",
					   chan->chan);
				continue;
			}
		}

		factor = 0;
		if (acs_usable_chan(chan))
			factor = chan->interference_factor;
		total_weight = 1;

		for (j = 1; j < n_chans; j++) {
			adj_chan = acs_find_chan(iface, chan->freq + (j * 20));
			if (!adj_chan)
				break;

			if (!chan_bw_allowed(adj_chan, bw, 1, 0)) {
				wpa_printf(MSG_DEBUG,
					   "ACS: PRI Channel %d: secondary channel %d BW %u is not supported",
					   chan->chan, adj_chan->chan, bw);
				break;
			}

			if (acs_usable_chan(adj_chan)) {
				factor += adj_chan->interference_factor;
				total_weight += 1;
			}
		}

		if (j != n_chans) {
			wpa_printf(MSG_DEBUG, "ACS: Channel %d: not enough bandwidth",
				   chan->chan);
			continue;
		}

		/* 2.4 GHz has overlapping 20 MHz channels. Include adjacent
		 * channel interference factor. */
		if (is_24ghz_mode(iface->current_mode->mode)) {
			for (j = 0; j < n_chans; j++) {
				adj_chan = acs_find_chan(iface, chan->freq +
							 (j * 20) - 5);
				if (adj_chan && acs_usable_chan(adj_chan)) {
					factor += ACS_ADJ_WEIGHT *
						adj_chan->interference_factor;
					total_weight += ACS_ADJ_WEIGHT;
				}

				adj_chan = acs_find_chan(iface, chan->freq +
							 (j * 20) - 10);
				if (adj_chan && acs_usable_chan(adj_chan)) {
					factor += ACS_NEXT_ADJ_WEIGHT *
						adj_chan->interference_factor;
					total_weight += ACS_NEXT_ADJ_WEIGHT;
				}

				adj_chan = acs_find_chan(iface, chan->freq +
							 (j * 20) + 5);
				if (adj_chan && acs_usable_chan(adj_chan)) {
					factor += ACS_ADJ_WEIGHT *
						adj_chan->interference_factor;
					total_weight += ACS_ADJ_WEIGHT;
				}

				adj_chan = acs_find_chan(iface, chan->freq +
							 (j * 20) + 10);
				if (adj_chan && acs_usable_chan(adj_chan)) {
					factor += ACS_NEXT_ADJ_WEIGHT *
						adj_chan->interference_factor;
					total_weight += ACS_NEXT_ADJ_WEIGHT;
				}
			}
		}

		factor /= total_weight;

		bias = NULL;
		if (iface->conf->acs_chan_bias) {
			for (k = 0; k < iface->conf->num_acs_chan_bias; k++) {
				bias = &iface->conf->acs_chan_bias[k];
				if (bias->channel == chan->chan)
					break;
				bias = NULL;
			}
		} else if (is_24ghz_mode(iface->current_mode->mode) &&
			   is_common_24ghz_chan(chan->chan)) {
			tmp_bias.channel = chan->chan;
			tmp_bias.bias = ACS_24GHZ_PREFER_1_6_11;
			bias = &tmp_bias;
		}

		if (bias) {
			factor *= bias->bias;
			wpa_printf(MSG_DEBUG,
				   "ACS:  * channel %d: total interference = %Lg (%f bias)",
				   chan->chan, factor, bias->bias);
		} else {
			wpa_printf(MSG_DEBUG,
				   "ACS:  * channel %d: total interference = %Lg",
				   chan->chan, factor);
		}

		if (acs_usable_chan(chan) &&
		    (!ideal_chan || factor < ideal_factor)) {
			ideal_factor = factor;
			ideal_chan = chan;
		}

		/* This channel would at least be usable */
		if (!rand_chan)
			rand_chan = chan;
	}

	if (ideal_chan) {
		wpa_printf(MSG_DEBUG, "ACS: Ideal channel is %d (%d MHz) with total interference factor of %Lg",
			   ideal_chan->chan, ideal_chan->freq, ideal_factor);
		return ideal_chan;
	}

	return rand_chan;
}