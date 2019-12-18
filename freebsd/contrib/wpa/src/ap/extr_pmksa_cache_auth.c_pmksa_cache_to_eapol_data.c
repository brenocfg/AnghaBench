#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rsn_pmksa_cache_entry {int /*<<< orphan*/  acct_multi_session_id; int /*<<< orphan*/  vlan_desc; int /*<<< orphan*/  eap_type_authsrv; int /*<<< orphan*/  radius_class; scalar_t__ cui; int /*<<< orphan*/  identity_len; scalar_t__ identity; } ;
struct hostapd_data {int dummy; } ;
struct TYPE_3__ {scalar_t__ count; scalar_t__ attr; } ;
struct eapol_state_machine {int /*<<< orphan*/  acct_multi_session_id; int /*<<< orphan*/  sta; int /*<<< orphan*/  eap_type_authsrv; TYPE_1__ radius_class; int /*<<< orphan*/  radius_cui; int /*<<< orphan*/  identity_len; scalar_t__ identity; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  ap_sta_set_vlan (struct hostapd_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_free (scalar_t__) ; 
 scalar_t__ os_malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memcpy (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radius_copy_class (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radius_free_class (TYPE_1__*) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,unsigned long) ; 
 int /*<<< orphan*/  wpabuf_dup (scalar_t__) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ ) ; 

void pmksa_cache_to_eapol_data(struct hostapd_data *hapd,
			       struct rsn_pmksa_cache_entry *entry,
			       struct eapol_state_machine *eapol)
{
	if (entry == NULL || eapol == NULL)
		return;

	if (entry->identity) {
		os_free(eapol->identity);
		eapol->identity = os_malloc(entry->identity_len);
		if (eapol->identity) {
			eapol->identity_len = entry->identity_len;
			os_memcpy(eapol->identity, entry->identity,
				  entry->identity_len);
		}
		wpa_hexdump_ascii(MSG_DEBUG, "STA identity from PMKSA",
				  eapol->identity, eapol->identity_len);
	}

	if (entry->cui) {
		wpabuf_free(eapol->radius_cui);
		eapol->radius_cui = wpabuf_dup(entry->cui);
	}

#ifndef CONFIG_NO_RADIUS
	radius_free_class(&eapol->radius_class);
	radius_copy_class(&eapol->radius_class, &entry->radius_class);
#endif /* CONFIG_NO_RADIUS */
	if (eapol->radius_class.attr) {
		wpa_printf(MSG_DEBUG, "Copied %lu Class attribute(s) from "
			   "PMKSA", (unsigned long) eapol->radius_class.count);
	}

	eapol->eap_type_authsrv = entry->eap_type_authsrv;
#ifndef CONFIG_NO_VLAN
	ap_sta_set_vlan(hapd, eapol->sta, entry->vlan_desc);
#endif /* CONFIG_NO_VLAN */

	eapol->acct_multi_session_id = entry->acct_multi_session_id;
}