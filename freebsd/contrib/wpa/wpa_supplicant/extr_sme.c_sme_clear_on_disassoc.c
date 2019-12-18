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
struct TYPE_2__ {scalar_t__ ft_used; scalar_t__ ft_ies; int /*<<< orphan*/  sae; int /*<<< orphan*/ * sae_token; scalar_t__ prev_bssid_set; } ;
struct wpa_supplicant {TYPE_1__ sme; } ;

/* Variables and functions */
 int /*<<< orphan*/  sae_clear_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sme_stop_sa_query (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  sme_update_ft_ies (struct wpa_supplicant*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ *) ; 

void sme_clear_on_disassoc(struct wpa_supplicant *wpa_s)
{
	wpa_s->sme.prev_bssid_set = 0;
#ifdef CONFIG_SAE
	wpabuf_free(wpa_s->sme.sae_token);
	wpa_s->sme.sae_token = NULL;
	sae_clear_data(&wpa_s->sme.sae);
#endif /* CONFIG_SAE */
#ifdef CONFIG_IEEE80211R
	if (wpa_s->sme.ft_ies || wpa_s->sme.ft_used)
		sme_update_ft_ies(wpa_s, NULL, NULL, 0);
#endif /* CONFIG_IEEE80211R */
#ifdef CONFIG_IEEE80211W
	sme_stop_sa_query(wpa_s);
#endif /* CONFIG_IEEE80211W */
}