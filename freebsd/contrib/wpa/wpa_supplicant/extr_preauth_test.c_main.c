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
typedef  int /*<<< orphan*/  wpa_s ;
typedef  int /*<<< orphan*/  u8 ;
struct wpa_supplicant {int /*<<< orphan*/  wpa; scalar_t__ auth_timed_out; TYPE_2__* conf; int /*<<< orphan*/ * ctrl_iface; } ;
struct preauth_test_data {int /*<<< orphan*/  wpa; scalar_t__ auth_timed_out; TYPE_2__* conf; int /*<<< orphan*/ * ctrl_iface; } ;
typedef  int /*<<< orphan*/  preauth_test ;
struct TYPE_4__ {char* ctrl_interface; TYPE_1__* ssid; } ;
struct TYPE_3__ {int /*<<< orphan*/  eap; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  eap_peer_unregister_methods () ; 
 scalar_t__ eap_register_methods () ; 
 int /*<<< orphan*/  eapol_test_poll ; 
 int /*<<< orphan*/  eapol_test_terminate ; 
 int /*<<< orphan*/  eapol_test_timeout ; 
 int /*<<< orphan*/  eloop_destroy () ; 
 scalar_t__ eloop_init () ; 
 int /*<<< orphan*/  eloop_register_signal_reconfig (int /*<<< orphan*/ ,struct wpa_supplicant*) ; 
 int /*<<< orphan*/  eloop_register_signal_terminate (int /*<<< orphan*/ ,struct wpa_supplicant*) ; 
 int /*<<< orphan*/  eloop_register_timeout (int,int,int /*<<< orphan*/ ,struct wpa_supplicant*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eloop_run () ; 
 scalar_t__ hwaddr_aton (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_memset (struct wpa_supplicant*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  os_program_deinit () ; 
 scalar_t__ os_program_init () ; 
 scalar_t__ pmksa_cache_set_current (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ rsn_preauth_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_eapol_clean (struct wpa_supplicant*) ; 
 TYPE_2__* wpa_config_read (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ wpa_debug_level ; 
 int wpa_debug_show_keys ; 
 int /*<<< orphan*/  wpa_init_conf (struct wpa_supplicant*,char*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * wpa_supplicant_ctrl_iface_init (struct wpa_supplicant*) ; 
 scalar_t__ wpa_supplicant_scard_init (struct wpa_supplicant*,TYPE_1__*) ; 

int main(int argc, char *argv[])
{
	struct wpa_supplicant wpa_s;
	int ret = 1;
	u8 bssid[ETH_ALEN];
	struct preauth_test_data preauth_test;

	if (os_program_init())
		return -1;

	os_memset(&preauth_test, 0, sizeof(preauth_test));

	wpa_debug_level = 0;
	wpa_debug_show_keys = 1;

	if (argc != 4) {
		printf("usage: preauth_test <conf> <target MAC address> "
		       "<ifname>\n");
		return -1;
	}

	if (hwaddr_aton(argv[2], bssid)) {
		printf("Failed to parse target address '%s'.\n", argv[2]);
		return -1;
	}

	if (eap_register_methods()) {
		wpa_printf(MSG_ERROR, "Failed to register EAP methods");
		return -1;
	}

	if (eloop_init()) {
		wpa_printf(MSG_ERROR, "Failed to initialize event loop");
		return -1;
	}

	os_memset(&wpa_s, 0, sizeof(wpa_s));
	wpa_s.conf = wpa_config_read(argv[1], NULL);
	if (wpa_s.conf == NULL) {
		printf("Failed to parse configuration file '%s'.\n", argv[1]);
		return -1;
	}
	if (wpa_s.conf->ssid == NULL) {
		printf("No networks defined.\n");
		return -1;
	}

	wpa_init_conf(&wpa_s, argv[3]);
	wpa_s.ctrl_iface = wpa_supplicant_ctrl_iface_init(&wpa_s);
	if (wpa_s.ctrl_iface == NULL) {
		printf("Failed to initialize control interface '%s'.\n"
		       "You may have another preauth_test process already "
		       "running or the file was\n"
		       "left by an unclean termination of preauth_test in "
		       "which case you will need\n"
		       "to manually remove this file before starting "
		       "preauth_test again.\n",
		       wpa_s.conf->ctrl_interface);
		return -1;
	}
	if (wpa_supplicant_scard_init(&wpa_s, wpa_s.conf->ssid))
		return -1;

	if (rsn_preauth_init(wpa_s.wpa, bssid, &wpa_s.conf->ssid->eap))
		return -1;

	eloop_register_timeout(30, 0, eapol_test_timeout, &preauth_test, NULL);
	eloop_register_timeout(0, 100000, eapol_test_poll, &wpa_s, NULL);
	eloop_register_signal_terminate(eapol_test_terminate, &wpa_s);
	eloop_register_signal_reconfig(eapol_test_terminate, &wpa_s);
	eloop_run();

	if (preauth_test.auth_timed_out)
		ret = -2;
	else {
		ret = pmksa_cache_set_current(wpa_s.wpa, NULL, bssid, NULL, 0,
					      NULL, 0) ? 0 : -3;
	}

	test_eapol_clean(&wpa_s);

	eap_peer_unregister_methods();

	eloop_destroy();

	os_program_deinit();

	return ret;
}