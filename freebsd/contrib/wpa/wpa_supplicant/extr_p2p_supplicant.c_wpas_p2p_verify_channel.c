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
struct wpa_supplicant {int /*<<< orphan*/  global; } ;
struct hostapd_hw_modes {int dummy; } ;
typedef  enum chan_allowed { ____Placeholder_chan_allowed } chan_allowed ;

/* Variables and functions */
 scalar_t__ BW160 ; 
 scalar_t__ BW40MINUS ; 
 scalar_t__ BW40PLUS ; 
 scalar_t__ BW80 ; 
 int HOSTAPD_CHAN_HT40MINUS ; 
 int HOSTAPD_CHAN_HT40PLUS ; 
 int NOT_ALLOWED ; 
 int NO_IR ; 
 int has_channel (int /*<<< orphan*/ ,struct hostapd_hw_modes*,scalar_t__,int*) ; 
 int wpas_p2p_verify_160mhz (struct wpa_supplicant*,struct hostapd_hw_modes*,scalar_t__,scalar_t__) ; 
 int wpas_p2p_verify_80mhz (struct wpa_supplicant*,struct hostapd_hw_modes*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static enum chan_allowed wpas_p2p_verify_channel(struct wpa_supplicant *wpa_s,
						 struct hostapd_hw_modes *mode,
						 u8 channel, u8 bw)
{
	int flag = 0;
	enum chan_allowed res, res2;

	res2 = res = has_channel(wpa_s->global, mode, channel, &flag);
	if (bw == BW40MINUS) {
		if (!(flag & HOSTAPD_CHAN_HT40MINUS))
			return NOT_ALLOWED;
		res2 = has_channel(wpa_s->global, mode, channel - 4, NULL);
	} else if (bw == BW40PLUS) {
		if (!(flag & HOSTAPD_CHAN_HT40PLUS))
			return NOT_ALLOWED;
		res2 = has_channel(wpa_s->global, mode, channel + 4, NULL);
	} else if (bw == BW80) {
		res2 = wpas_p2p_verify_80mhz(wpa_s, mode, channel, bw);
	} else if (bw == BW160) {
		res2 = wpas_p2p_verify_160mhz(wpa_s, mode, channel, bw);
	}

	if (res == NOT_ALLOWED || res2 == NOT_ALLOWED)
		return NOT_ALLOWED;
	if (res == NO_IR || res2 == NO_IR)
		return NO_IR;
	return res;
}