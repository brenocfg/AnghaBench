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
typedef  int /*<<< orphan*/  u8 ;
struct wpa_supplicant {int /*<<< orphan*/  p2p_oob_dev_pw_id; TYPE_2__* global; TYPE_1__* conf; } ;
struct wpa_ssid {int /*<<< orphan*/  ssid_len; int /*<<< orphan*/ * ssid; } ;
typedef  enum p2p_wps_method { ____Placeholder_p2p_wps_method } p2p_wps_method ;
struct TYPE_4__ {int /*<<< orphan*/  p2p; } ;
struct TYPE_3__ {scalar_t__ persistent_reconnect; } ;

/* Variables and functions */
 int WPS_NFC ; 
 int p2p_authorize (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,int,int /*<<< orphan*/  const*,unsigned int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wpas_p2p_auth_go_neg(struct wpa_supplicant *wpa_s,
				const u8 *peer_addr,
				enum p2p_wps_method wps_method,
				int go_intent, const u8 *own_interface_addr,
				unsigned int force_freq, int persistent_group,
				struct wpa_ssid *ssid, unsigned int pref_freq)
{
	if (persistent_group && wpa_s->conf->persistent_reconnect)
		persistent_group = 2;

	return p2p_authorize(wpa_s->global->p2p, peer_addr, wps_method,
			     go_intent, own_interface_addr, force_freq,
			     persistent_group, ssid ? ssid->ssid : NULL,
			     ssid ? ssid->ssid_len : 0, pref_freq,
			     wps_method == WPS_NFC ? wpa_s->p2p_oob_dev_pw_id :
			     0);
}