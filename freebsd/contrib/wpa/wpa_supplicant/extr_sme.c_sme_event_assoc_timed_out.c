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
typedef  union wpa_event_data {int dummy; } wpa_event_data ;
struct wpa_supplicant {int /*<<< orphan*/  pending_bssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  wpa_dbg (struct wpa_supplicant*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpa_supplicant_mark_disassoc (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpas_connection_failed (struct wpa_supplicant*,int /*<<< orphan*/ ) ; 

void sme_event_assoc_timed_out(struct wpa_supplicant *wpa_s,
			       union wpa_event_data *data)
{
	wpa_dbg(wpa_s, MSG_DEBUG, "SME: Association timed out");
	wpas_connection_failed(wpa_s, wpa_s->pending_bssid);
	wpa_supplicant_mark_disassoc(wpa_s);
}