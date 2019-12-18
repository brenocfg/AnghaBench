#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wps_er_sta {struct wps_er_sta* cred; int /*<<< orphan*/  http; struct wps_er_sta* dev_name; struct wps_er_sta* serial_number; struct wps_er_sta* model_number; struct wps_er_sta* model_name; struct wps_er_sta* manufacturer; scalar_t__ wps; TYPE_2__* ap; } ;
struct TYPE_4__ {TYPE_1__* er; } ;
struct TYPE_3__ {int /*<<< orphan*/  wps; } ;

/* Variables and functions */
 int /*<<< orphan*/  WPS_EV_ER_ENROLLEE_REMOVE ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct wps_er_sta*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  http_client_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_free (struct wps_er_sta*) ; 
 int /*<<< orphan*/  wps_deinit (scalar_t__) ; 
 int /*<<< orphan*/  wps_er_sta_event (int /*<<< orphan*/ ,struct wps_er_sta*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wps_er_sta_timeout ; 

__attribute__((used)) static void wps_er_sta_free(struct wps_er_sta *sta)
{
	wps_er_sta_event(sta->ap->er->wps, sta, WPS_EV_ER_ENROLLEE_REMOVE);
	if (sta->wps)
		wps_deinit(sta->wps);
	os_free(sta->manufacturer);
	os_free(sta->model_name);
	os_free(sta->model_number);
	os_free(sta->serial_number);
	os_free(sta->dev_name);
	http_client_free(sta->http);
	eloop_cancel_timeout(wps_er_sta_timeout, sta, NULL);
	os_free(sta->cred);
	os_free(sta);
}