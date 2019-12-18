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
struct wpabuf {int dummy; } ;
struct wpa_supplicant {TYPE_2__* conf; } ;
struct wpa_cred {scalar_t__ roaming_consortium_len; scalar_t__ num_roaming_consortiums; int /*<<< orphan*/  roaming_consortium; int /*<<< orphan*/  eap_method; struct wpa_cred* next; } ;
struct wpa_bss {TYPE_1__* anqp; } ;
struct TYPE_4__ {struct wpa_cred* cred; } ;
struct TYPE_3__ {struct wpabuf* roaming_consortium; } ;

/* Variables and functions */
 int /*<<< orphan*/  WLAN_EID_ROAMING_CONSORTIUM ; 
 scalar_t__ cred_below_min_backhaul (struct wpa_supplicant*,struct wpa_cred*,struct wpa_bss*) ; 
 scalar_t__ cred_conn_capab_missing (struct wpa_supplicant*,struct wpa_cred*,struct wpa_bss*) ; 
 scalar_t__ cred_excluded_ssid (struct wpa_cred*,struct wpa_bss*) ; 
 scalar_t__ cred_no_required_oi_match (struct wpa_cred*,struct wpa_bss*) ; 
 scalar_t__ cred_over_max_bss_load (struct wpa_supplicant*,struct wpa_cred*,struct wpa_bss*) ; 
 scalar_t__ cred_prio_cmp (struct wpa_cred*,struct wpa_cred*) ; 
 int /*<<< orphan*/  cred_roaming_consortiums_match (int /*<<< orphan*/  const*,struct wpabuf const*,struct wpa_cred*) ; 
 int /*<<< orphan*/  roaming_consortium_match (int /*<<< orphan*/  const*,struct wpabuf const*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * wpa_bss_get_ie (struct wpa_bss*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct wpa_cred * interworking_credentials_available_roaming_consortium(
	struct wpa_supplicant *wpa_s, struct wpa_bss *bss, int ignore_bw,
	int *excluded)
{
	struct wpa_cred *cred, *selected = NULL;
	const u8 *ie;
	const struct wpabuf *anqp;
	int is_excluded = 0;

	ie = wpa_bss_get_ie(bss, WLAN_EID_ROAMING_CONSORTIUM);
	anqp = bss->anqp ? bss->anqp->roaming_consortium : NULL;

	if (!ie && !anqp)
		return NULL;

	if (wpa_s->conf->cred == NULL)
		return NULL;

	for (cred = wpa_s->conf->cred; cred; cred = cred->next) {
		if (cred->roaming_consortium_len == 0 &&
		    cred->num_roaming_consortiums == 0)
			continue;

		if (!cred->eap_method)
			continue;

		if ((cred->roaming_consortium_len == 0 ||
		     !roaming_consortium_match(ie, anqp,
					       cred->roaming_consortium,
					       cred->roaming_consortium_len)) &&
		    !cred_roaming_consortiums_match(ie, anqp, cred))
			continue;

		if (cred_no_required_oi_match(cred, bss))
			continue;
		if (!ignore_bw && cred_below_min_backhaul(wpa_s, cred, bss))
			continue;
		if (!ignore_bw && cred_over_max_bss_load(wpa_s, cred, bss))
			continue;
		if (!ignore_bw && cred_conn_capab_missing(wpa_s, cred, bss))
			continue;
		if (cred_excluded_ssid(cred, bss)) {
			if (excluded == NULL)
				continue;
			if (selected == NULL) {
				selected = cred;
				is_excluded = 1;
			}
		} else {
			if (selected == NULL || is_excluded ||
			    cred_prio_cmp(selected, cred) < 0) {
				selected = cred;
				is_excluded = 0;
			}
		}
	}

	if (excluded)
		*excluded = is_excluded;

	return selected;
}