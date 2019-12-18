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
struct wpa_sm {int /*<<< orphan*/  mgmt_group_cipher; } ;
struct wpa_igtk_kde {int dummy; } ;
struct wpa_eapol_ie_parse {scalar_t__ igtk_len; scalar_t__ igtk; } ;

/* Variables and functions */
 scalar_t__ WPA_IGTK_KDE_PREFIX_LEN ; 
 size_t wpa_cipher_key_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_cipher_valid_mgmt_group (int /*<<< orphan*/ ) ; 
 scalar_t__ wpa_supplicant_install_igtk (struct wpa_sm*,struct wpa_igtk_kde const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ieee80211w_set_keys(struct wpa_sm *sm,
			       struct wpa_eapol_ie_parse *ie)
{
#ifdef CONFIG_IEEE80211W
	if (!wpa_cipher_valid_mgmt_group(sm->mgmt_group_cipher))
		return 0;

	if (ie->igtk) {
		size_t len;
		const struct wpa_igtk_kde *igtk;

		len = wpa_cipher_key_len(sm->mgmt_group_cipher);
		if (ie->igtk_len != WPA_IGTK_KDE_PREFIX_LEN + len)
			return -1;

		igtk = (const struct wpa_igtk_kde *) ie->igtk;
		if (wpa_supplicant_install_igtk(sm, igtk, 0) < 0)
			return -1;
	}

	return 0;
#else /* CONFIG_IEEE80211W */
	return 0;
#endif /* CONFIG_IEEE80211W */
}