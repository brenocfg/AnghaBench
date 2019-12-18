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
struct wpa_supplicant {int /*<<< orphan*/  conf; int /*<<< orphan*/ * ctrl_iface; int /*<<< orphan*/  scard; int /*<<< orphan*/  wpa; } ;

/* Variables and functions */
 int /*<<< orphan*/  pmksa_candidate_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsn_preauth_deinit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scard_deinit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_config_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_sm_deinit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_supplicant_ctrl_iface_deinit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_eapol_clean(struct wpa_supplicant *wpa_s)
{
	rsn_preauth_deinit(wpa_s->wpa);
	pmksa_candidate_free(wpa_s->wpa);
	wpa_sm_deinit(wpa_s->wpa);
	scard_deinit(wpa_s->scard);
	if (wpa_s->ctrl_iface) {
		wpa_supplicant_ctrl_iface_deinit(wpa_s->ctrl_iface);
		wpa_s->ctrl_iface = NULL;
	}
	wpa_config_free(wpa_s->conf);
}