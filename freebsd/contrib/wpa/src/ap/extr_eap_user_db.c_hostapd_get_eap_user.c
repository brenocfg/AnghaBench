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
typedef  int /*<<< orphan*/  wsc_registrar ;
typedef  int /*<<< orphan*/  wsc_enrollee ;
typedef  int /*<<< orphan*/  u8 ;
typedef  struct hostapd_eap_user {int phase2; size_t identity_len; struct hostapd_eap_user const* next; int /*<<< orphan*/  const* identity; scalar_t__ wildcard_prefix; int /*<<< orphan*/  password_len; int /*<<< orphan*/ * password; TYPE_1__* methods; } const hostapd_eap_user ;
struct hostapd_data {struct hostapd_bss_config* conf; } ;
struct hostapd_bss_config {scalar_t__ eap_user_sqlite; scalar_t__ ap_pin; scalar_t__ wps_state; struct hostapd_eap_user const* eap_user; } ;
struct TYPE_2__ {int /*<<< orphan*/  vendor; void* method; } ;

/* Variables and functions */
 int /*<<< orphan*/  const* WSC_ID_ENROLLEE ; 
 size_t WSC_ID_ENROLLEE_LEN ; 
 int /*<<< orphan*/  const* WSC_ID_REGISTRAR ; 
 size_t WSC_ID_REGISTRAR_LEN ; 
 void* eap_server_get_type (char*,int /*<<< orphan*/ *) ; 
 struct hostapd_eap_user const* eap_user_sqlite_get (struct hostapd_data*,int /*<<< orphan*/  const*,size_t,int) ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  os_memset (struct hostapd_eap_user const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  os_strlen (scalar_t__) ; 

const struct hostapd_eap_user *
hostapd_get_eap_user(struct hostapd_data *hapd, const u8 *identity,
		     size_t identity_len, int phase2)
{
	const struct hostapd_bss_config *conf = hapd->conf;
	struct hostapd_eap_user *user = conf->eap_user;

#ifdef CONFIG_WPS
	if (conf->wps_state && identity_len == WSC_ID_ENROLLEE_LEN &&
	    os_memcmp(identity, WSC_ID_ENROLLEE, WSC_ID_ENROLLEE_LEN) == 0) {
		static struct hostapd_eap_user wsc_enrollee;
		os_memset(&wsc_enrollee, 0, sizeof(wsc_enrollee));
		wsc_enrollee.methods[0].method = eap_server_get_type(
			"WSC", &wsc_enrollee.methods[0].vendor);
		return &wsc_enrollee;
	}

	if (conf->wps_state && identity_len == WSC_ID_REGISTRAR_LEN &&
	    os_memcmp(identity, WSC_ID_REGISTRAR, WSC_ID_REGISTRAR_LEN) == 0) {
		static struct hostapd_eap_user wsc_registrar;
		os_memset(&wsc_registrar, 0, sizeof(wsc_registrar));
		wsc_registrar.methods[0].method = eap_server_get_type(
			"WSC", &wsc_registrar.methods[0].vendor);
		wsc_registrar.password = (u8 *) conf->ap_pin;
		wsc_registrar.password_len = conf->ap_pin ?
			os_strlen(conf->ap_pin) : 0;
		return &wsc_registrar;
	}
#endif /* CONFIG_WPS */

	while (user) {
		if (!phase2 && user->identity == NULL) {
			/* Wildcard match */
			break;
		}

		if (user->phase2 == !!phase2 && user->wildcard_prefix &&
		    identity_len >= user->identity_len &&
		    os_memcmp(user->identity, identity, user->identity_len) ==
		    0) {
			/* Wildcard prefix match */
			break;
		}

		if (user->phase2 == !!phase2 &&
		    user->identity_len == identity_len &&
		    os_memcmp(user->identity, identity, identity_len) == 0)
			break;
		user = user->next;
	}

#ifdef CONFIG_SQLITE
	if (user == NULL && conf->eap_user_sqlite) {
		return eap_user_sqlite_get(hapd, identity, identity_len,
					   phase2);
	}
#endif /* CONFIG_SQLITE */

	return user;
}