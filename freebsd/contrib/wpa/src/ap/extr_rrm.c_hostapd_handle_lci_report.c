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
typedef  scalar_t__ u8 ;
struct hostapd_data {scalar_t__ lci_req_token; scalar_t__ lci_req_active; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct hostapd_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hostapd_lci_rep_timeout_handler ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,scalar_t__,...) ; 

__attribute__((used)) static void hostapd_handle_lci_report(struct hostapd_data *hapd, u8 token,
				      const u8 *pos, size_t len)
{
	if (!hapd->lci_req_active || hapd->lci_req_token != token) {
		wpa_printf(MSG_DEBUG, "Unexpected LCI report, token %u", token);
		return;
	}

	hapd->lci_req_active = 0;
	eloop_cancel_timeout(hostapd_lci_rep_timeout_handler, hapd, NULL);
	wpa_printf(MSG_DEBUG, "LCI report token %u len %zu", token, len);
}