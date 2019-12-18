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
struct wps_er_ap {int /*<<< orphan*/  list; scalar_t__ subscribed; int /*<<< orphan*/ * wps; int /*<<< orphan*/ * http; int /*<<< orphan*/  location; int /*<<< orphan*/  addr; } ;
struct wps_er {int /*<<< orphan*/  ap_unsubscribing; int /*<<< orphan*/  wps; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  WPS_EV_ER_AP_REMOVE ; 
 int /*<<< orphan*/  dl_list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dl_list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct wps_er*,struct wps_er_ap*) ; 
 int /*<<< orphan*/  http_client_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inet_ntoa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wps_deinit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wps_er_ap_event (int /*<<< orphan*/ ,struct wps_er_ap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wps_er_ap_free (struct wps_er_ap*) ; 
 int /*<<< orphan*/  wps_er_ap_timeout ; 
 int /*<<< orphan*/  wps_er_ap_unsubscribe (struct wps_er*,struct wps_er_ap*) ; 
 int /*<<< orphan*/  wps_er_sta_remove_all (struct wps_er_ap*) ; 

__attribute__((used)) static void wps_er_ap_remove_entry(struct wps_er *er, struct wps_er_ap *ap)
{
	wpa_printf(MSG_DEBUG, "WPS ER: Removing AP entry for %s (%s)",
		   inet_ntoa(ap->addr), ap->location);
	eloop_cancel_timeout(wps_er_ap_timeout, er, ap);
	wps_er_sta_remove_all(ap);
	wps_er_ap_event(er->wps, ap, WPS_EV_ER_AP_REMOVE);
	http_client_free(ap->http);
	ap->http = NULL;
	if (ap->wps) {
		wps_deinit(ap->wps);
		ap->wps = NULL;
	}

	dl_list_del(&ap->list);
	if (ap->subscribed) {
		dl_list_add(&er->ap_unsubscribing, &ap->list);
		wps_er_ap_unsubscribe(er, ap);
	} else
		wps_er_ap_free(ap);
}