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
typedef  scalar_t__ u8 ;
struct wpa_supplicant {int dummy; } ;
struct oper_class_map {scalar_t__ p2p; scalar_t__ min_chan; scalar_t__ max_chan; scalar_t__ inc; scalar_t__ mode; scalar_t__ bw; scalar_t__ op_class; } ;
struct hostapd_hw_modes {int dummy; } ;
typedef  enum chan_allowed { ____Placeholder_chan_allowed } chan_allowed ;

/* Variables and functions */
 int ALLOWED ; 
 scalar_t__ BW40MINUS ; 
 scalar_t__ BW40PLUS ; 
 scalar_t__ HOSTAPD_MODE_IEEE80211A ; 
 scalar_t__ NO_P2P_SUPP ; 
 struct oper_class_map* global_op_class ; 
 int wpas_p2p_verify_channel (struct wpa_supplicant*,struct hostapd_hw_modes*,scalar_t__,scalar_t__) ; 

int wpas_p2p_get_ht40_mode(struct wpa_supplicant *wpa_s,
			   struct hostapd_hw_modes *mode, u8 channel)
{
	int op;
	enum chan_allowed ret;

	for (op = 0; global_op_class[op].op_class; op++) {
		const struct oper_class_map *o = &global_op_class[op];
		u8 ch;

		if (o->p2p == NO_P2P_SUPP)
			continue;

		for (ch = o->min_chan; ch <= o->max_chan; ch += o->inc) {
			if (o->mode != HOSTAPD_MODE_IEEE80211A ||
			    (o->bw != BW40PLUS && o->bw != BW40MINUS) ||
			    ch != channel)
				continue;
			ret = wpas_p2p_verify_channel(wpa_s, mode, ch, o->bw);
			if (ret == ALLOWED)
				return (o->bw == BW40MINUS) ? -1 : 1;
		}
	}
	return 0;
}