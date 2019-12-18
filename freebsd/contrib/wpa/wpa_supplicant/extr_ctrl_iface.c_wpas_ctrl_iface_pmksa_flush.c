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
struct wpa_supplicant {int /*<<< orphan*/  wpa; } ;

/* Variables and functions */
 int /*<<< orphan*/  wpa_sm_pmksa_cache_flush (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpas_ap_pmksa_cache_flush (struct wpa_supplicant*) ; 

__attribute__((used)) static void wpas_ctrl_iface_pmksa_flush(struct wpa_supplicant *wpa_s)
{
	wpa_sm_pmksa_cache_flush(wpa_s->wpa, NULL);
#ifdef CONFIG_AP
	wpas_ap_pmksa_cache_flush(wpa_s);
#endif /* CONFIG_AP */
}