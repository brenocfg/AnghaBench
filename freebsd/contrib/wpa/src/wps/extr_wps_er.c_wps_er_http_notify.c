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
struct wps_er {unsigned int event_id; } ;
struct http_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 unsigned int atoi (char*) ; 
 char* http_request_get_uri (struct http_request*) ; 
 char* os_strchr (char*,char) ; 
 scalar_t__ os_strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wps_er_http_event (struct wps_er*,struct http_request*,unsigned int) ; 
 int /*<<< orphan*/  wps_er_http_resp_not_found (struct http_request*) ; 

__attribute__((used)) static void wps_er_http_notify(struct wps_er *er, struct http_request *req)
{
	char *uri = http_request_get_uri(req);

	if (os_strncmp(uri, "/event/", 7) == 0) {
		unsigned int event_id;
		char *pos;
		event_id = atoi(uri + 7);
		if (event_id != er->event_id) {
			wpa_printf(MSG_DEBUG, "WPS ER: HTTP event for an "
				   "unknown event id %u", event_id);
			return;
		}
		pos = os_strchr(uri + 7, '/');
		if (pos == NULL)
			return;
		pos++;
		wps_er_http_event(er, req, atoi(pos));
	} else {
		wpa_printf(MSG_DEBUG, "WPS ER: Unknown HTTP NOTIFY for '%s'",
			   uri);
		wps_er_http_resp_not_found(req);
	}
}