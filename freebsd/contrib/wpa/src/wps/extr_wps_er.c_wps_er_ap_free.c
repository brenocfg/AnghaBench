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
struct wps_er_ap {struct wps_er_ap* ap_settings; struct wps_er_ap* event_sub_url; struct wps_er_ap* control_url; struct wps_er_ap* scpd_url; struct wps_er_ap* upc; struct wps_er_ap* udn; struct wps_er_ap* serial_number; struct wps_er_ap* model_url; struct wps_er_ap* model_number; struct wps_er_ap* model_name; struct wps_er_ap* model_description; struct wps_er_ap* manufacturer_url; struct wps_er_ap* manufacturer; struct wps_er_ap* friendly_name; struct wps_er_ap* location; int /*<<< orphan*/ * http; } ;

/* Variables and functions */
 int /*<<< orphan*/  http_client_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (struct wps_er_ap*) ; 

__attribute__((used)) static void wps_er_ap_free(struct wps_er_ap *ap)
{
	http_client_free(ap->http);
	ap->http = NULL;

	os_free(ap->location);
	os_free(ap->friendly_name);
	os_free(ap->manufacturer);
	os_free(ap->manufacturer_url);
	os_free(ap->model_description);
	os_free(ap->model_name);
	os_free(ap->model_number);
	os_free(ap->model_url);
	os_free(ap->serial_number);
	os_free(ap->udn);
	os_free(ap->upc);

	os_free(ap->scpd_url);
	os_free(ap->control_url);
	os_free(ap->event_sub_url);

	os_free(ap->ap_settings);

	os_free(ap);
}