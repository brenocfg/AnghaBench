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
struct wps_er_ap {int /*<<< orphan*/  list; int /*<<< orphan*/  location; int /*<<< orphan*/  addr; } ;
struct wps_er {int /*<<< orphan*/  ap_unsubscribing; scalar_t__ deinitializing; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  dl_list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ dl_list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inet_ntoa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wps_er_ap_free (struct wps_er_ap*) ; 
 int /*<<< orphan*/  wps_er_deinit_finish (struct wps_er*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void wps_er_ap_unsubscribed(struct wps_er *er, struct wps_er_ap *ap)
{
	wpa_printf(MSG_DEBUG, "WPS ER: Unsubscribed from AP %s (%s)",
		   inet_ntoa(ap->addr), ap->location);
	dl_list_del(&ap->list);
	wps_er_ap_free(ap);

	if (er->deinitializing && dl_list_empty(&er->ap_unsubscribing))
		wps_er_deinit_finish(er, NULL);
}