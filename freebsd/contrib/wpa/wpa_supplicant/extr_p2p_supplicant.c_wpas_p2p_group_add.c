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
struct wpa_supplicant {TYPE_1__* global; int /*<<< orphan*/  p2p_go_do_acs; } ;
struct p2p_go_neg_results {int persistent_group; } ;
struct TYPE_2__ {int /*<<< orphan*/ * p2p; int /*<<< orphan*/ * add_psk; scalar_t__ p2p_disabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p2p_go_params (int /*<<< orphan*/ *,struct p2p_go_neg_results*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 struct wpa_supplicant* wpas_p2p_get_group_iface (struct wpa_supplicant*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ wpas_p2p_init_go_params (struct wpa_supplicant*,struct p2p_go_neg_results*,int,int,int,int,int,int,int /*<<< orphan*/ *) ; 
 int wpas_p2p_select_go_freq (struct wpa_supplicant*,int) ; 
 int /*<<< orphan*/  wpas_p2p_stop_find_oper (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpas_start_wps_go (struct wpa_supplicant*,struct p2p_go_neg_results*,int /*<<< orphan*/ ) ; 

int wpas_p2p_group_add(struct wpa_supplicant *wpa_s, int persistent_group,
		       int freq, int vht_center_freq2, int ht40, int vht,
		       int max_oper_chwidth, int he)
{
	struct p2p_go_neg_results params;

	if (wpa_s->global->p2p_disabled || wpa_s->global->p2p == NULL)
		return -1;

	os_free(wpa_s->global->add_psk);
	wpa_s->global->add_psk = NULL;

	/* Make sure we are not running find during connection establishment */
	wpa_printf(MSG_DEBUG, "P2P: Stop any on-going P2P FIND");
	wpas_p2p_stop_find_oper(wpa_s);

	if (!wpa_s->p2p_go_do_acs) {
		freq = wpas_p2p_select_go_freq(wpa_s, freq);
		if (freq < 0)
			return -1;
	}

	if (wpas_p2p_init_go_params(wpa_s, &params, freq, vht_center_freq2,
				    ht40, vht, max_oper_chwidth, he, NULL))
		return -1;

	p2p_go_params(wpa_s->global->p2p, &params);
	params.persistent_group = persistent_group;

	wpa_s = wpas_p2p_get_group_iface(wpa_s, 0, 1);
	if (wpa_s == NULL)
		return -1;
	wpas_start_wps_go(wpa_s, &params, 0);

	return 0;
}