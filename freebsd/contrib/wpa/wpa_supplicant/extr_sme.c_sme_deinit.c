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
struct wpa_supplicant {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct wpa_supplicant*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sme_assoc_timer ; 
 int /*<<< orphan*/  sme_auth_timer ; 
 int /*<<< orphan*/  sme_clear_on_disassoc (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  sme_obss_scan_timeout ; 

void sme_deinit(struct wpa_supplicant *wpa_s)
{
	sme_clear_on_disassoc(wpa_s);

	eloop_cancel_timeout(sme_assoc_timer, wpa_s, NULL);
	eloop_cancel_timeout(sme_auth_timer, wpa_s, NULL);
	eloop_cancel_timeout(sme_obss_scan_timeout, wpa_s, NULL);
}