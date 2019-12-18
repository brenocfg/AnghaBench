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
struct wps_er_sta {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  dl_list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wps_er_sta_free (struct wps_er_sta*) ; 

__attribute__((used)) static void wps_er_sta_timeout(void *eloop_data, void *user_ctx)
{
	struct wps_er_sta *sta = eloop_data;
	wpa_printf(MSG_DEBUG, "WPS ER: STA entry timed out");
	dl_list_del(&sta->list);
	wps_er_sta_free(sta);
}