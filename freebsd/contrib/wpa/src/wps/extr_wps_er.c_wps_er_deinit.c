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
struct wps_er {int deinitializing; void (* deinit_done_cb ) (void*) ;void* deinit_done_ctx; int /*<<< orphan*/  ap_unsubscribing; int /*<<< orphan*/  http_srv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ dl_list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eloop_register_timeout (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wps_er*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  http_server_deinit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wps_er_ap_remove_all (struct wps_er*) ; 
 int /*<<< orphan*/  wps_er_deinit_finish ; 
 int /*<<< orphan*/  wps_er_ssdp_deinit (struct wps_er*) ; 

void wps_er_deinit(struct wps_er *er, void (*cb)(void *ctx), void *ctx)
{
	if (er == NULL)
		return;
	http_server_deinit(er->http_srv);
	wps_er_ap_remove_all(er);
	wps_er_ssdp_deinit(er);
	eloop_register_timeout(dl_list_empty(&er->ap_unsubscribing) ? 0 : 5, 0,
			       wps_er_deinit_finish, er, NULL);
	wpa_printf(MSG_DEBUG, "WPS ER: Finish deinit from timeout");
	er->deinitializing = 1;
	er->deinit_done_cb = cb;
	er->deinit_done_ctx = ctx;
}