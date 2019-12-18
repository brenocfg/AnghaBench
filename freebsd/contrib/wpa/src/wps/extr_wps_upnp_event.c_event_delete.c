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
struct wps_event_ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  event_clean (struct wps_event_*) ; 
 int /*<<< orphan*/  os_free (struct wps_event_*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,struct wps_event_*) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void event_delete(struct wps_event_ *e)
{
	wpa_printf(MSG_DEBUG, "WPS UPnP: Delete event %p", e);
	event_clean(e);
	wpabuf_free(e->data);
	os_free(e);
}