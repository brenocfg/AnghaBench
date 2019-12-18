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
struct wpa_supplicant {int /*<<< orphan*/  p2p_oob_dev_pw_id; int /*<<< orphan*/  p2p_pd_before_go_neg; TYPE_1__* global; scalar_t__ p2p_go_ht40; TYPE_2__* conf; } ;
struct wpa_ssid {int /*<<< orphan*/  ssid_len; int /*<<< orphan*/ * ssid; } ;
typedef  enum p2p_wps_method { ____Placeholder_p2p_wps_method } p2p_wps_method ;
struct TYPE_4__ {scalar_t__ persistent_reconnect; } ;
struct TYPE_3__ {int /*<<< orphan*/  p2p; } ;

/* Variables and functions */
 int WPS_NFC ; 
 int p2p_connect (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,int,int /*<<< orphan*/  const*,unsigned int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p2p_set_config_timeout (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int wpas_p2p_start_go_neg(struct wpa_supplicant *wpa_s,
				 const u8 *peer_addr,
				 enum p2p_wps_method wps_method,
				 int go_intent, const u8 *own_interface_addr,
				 unsigned int force_freq, int persistent_group,
				 struct wpa_ssid *ssid, unsigned int pref_freq)
{
	if (persistent_group && wpa_s->conf->persistent_reconnect)
		persistent_group = 2;

	/*
	 * Increase GO config timeout if HT40 is used since it takes some time
	 * to scan channels for coex purposes before the BSS can be started.
	 */
	p2p_set_config_timeout(wpa_s->global->p2p,
			       wpa_s->p2p_go_ht40 ? 255 : 100, 20);

	return p2p_connect(wpa_s->global->p2p, peer_addr, wps_method,
			   go_intent, own_interface_addr, force_freq,
			   persistent_group, ssid ? ssid->ssid : NULL,
			   ssid ? ssid->ssid_len : 0,
			   wpa_s->p2p_pd_before_go_neg, pref_freq,
			   wps_method == WPS_NFC ? wpa_s->p2p_oob_dev_pw_id :
			   0);
}