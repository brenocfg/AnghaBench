#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_5__ {int own_ie_override_len; int wpa; int /*<<< orphan*/  wpa_key_mgmt; int /*<<< orphan*/ * own_ie_override; } ;
struct wpa_authenticator {int wpa_ie_len; int /*<<< orphan*/ * wpa_ie; TYPE_1__ conf; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int WPA_PROTO_OSEN ; 
 int WPA_PROTO_RSN ; 
 int WPA_PROTO_WPA ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 void* os_malloc (int) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ wpa_key_mgmt_ft (int /*<<< orphan*/ ) ; 
 int wpa_write_mdie (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * wpa_write_osen (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int wpa_write_rsn_ie (TYPE_1__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int wpa_write_wpa_ie (TYPE_1__*,int /*<<< orphan*/ *,int) ; 

int wpa_auth_gen_wpa_ie(struct wpa_authenticator *wpa_auth)
{
	u8 *pos, buf[128];
	int res;

#ifdef CONFIG_TESTING_OPTIONS
	if (wpa_auth->conf.own_ie_override_len) {
		wpa_hexdump(MSG_DEBUG, "WPA: Forced own IE(s) for testing",
			    wpa_auth->conf.own_ie_override,
			    wpa_auth->conf.own_ie_override_len);
		os_free(wpa_auth->wpa_ie);
		wpa_auth->wpa_ie =
			os_malloc(wpa_auth->conf.own_ie_override_len);
		if (wpa_auth->wpa_ie == NULL)
			return -1;
		os_memcpy(wpa_auth->wpa_ie, wpa_auth->conf.own_ie_override,
			  wpa_auth->conf.own_ie_override_len);
		wpa_auth->wpa_ie_len = wpa_auth->conf.own_ie_override_len;
		return 0;
	}
#endif /* CONFIG_TESTING_OPTIONS */

	pos = buf;

	if (wpa_auth->conf.wpa == WPA_PROTO_OSEN) {
		pos = wpa_write_osen(&wpa_auth->conf, pos);
	}
	if (wpa_auth->conf.wpa & WPA_PROTO_RSN) {
		res = wpa_write_rsn_ie(&wpa_auth->conf,
				       pos, buf + sizeof(buf) - pos, NULL);
		if (res < 0)
			return res;
		pos += res;
	}
#ifdef CONFIG_IEEE80211R_AP
	if (wpa_key_mgmt_ft(wpa_auth->conf.wpa_key_mgmt)) {
		res = wpa_write_mdie(&wpa_auth->conf, pos,
				     buf + sizeof(buf) - pos);
		if (res < 0)
			return res;
		pos += res;
	}
#endif /* CONFIG_IEEE80211R_AP */
	if (wpa_auth->conf.wpa & WPA_PROTO_WPA) {
		res = wpa_write_wpa_ie(&wpa_auth->conf,
				       pos, buf + sizeof(buf) - pos);
		if (res < 0)
			return res;
		pos += res;
	}

	os_free(wpa_auth->wpa_ie);
	wpa_auth->wpa_ie = os_malloc(pos - buf);
	if (wpa_auth->wpa_ie == NULL)
		return -1;
	os_memcpy(wpa_auth->wpa_ie, buf, pos - buf);
	wpa_auth->wpa_ie_len = pos - buf;

	return 0;
}