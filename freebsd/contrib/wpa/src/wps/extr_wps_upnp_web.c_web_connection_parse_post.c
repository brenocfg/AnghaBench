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
struct wpabuf {int dummy; } ;
struct upnp_wps_device_sm {int dummy; } ;
struct sockaddr_in {int dummy; } ;
struct http_request {int dummy; } ;
typedef  enum http_reply_code { ____Placeholder_http_reply_code } http_reply_code ;

/* Variables and functions */
 int HTTP_NOT_FOUND ; 
 int HTTP_OK ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int UPNP_INVALID_ACTION ; 
 int /*<<< orphan*/  UPNP_WPS_DEVICE_CONTROL_FILE ; 
 char* http_request_get_data (struct http_request*) ; 
 scalar_t__ os_strcasecmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_strncasecmp (char*,char const*,size_t) ; 
 int /*<<< orphan*/  web_connection_send_reply (struct http_request*,int,char const*,size_t,struct wpabuf*,char const*) ; 
 char* web_get_action (struct http_request*,size_t*) ; 
 int web_process_get_device_info (struct upnp_wps_device_sm*,struct wpabuf**,char const**) ; 
 int web_process_put_message (struct upnp_wps_device_sm*,char*,struct wpabuf**,char const**) ; 
 int web_process_put_wlan_response (struct upnp_wps_device_sm*,char*,struct wpabuf**,char const**) ; 
 int web_process_set_selected_registrar (struct upnp_wps_device_sm*,struct sockaddr_in*,char*,struct wpabuf**,char const**) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 

__attribute__((used)) static void web_connection_parse_post(struct upnp_wps_device_sm *sm,
				      struct sockaddr_in *cli,
				      struct http_request *req,
				      const char *filename)
{
	enum http_reply_code ret;
	char *data = http_request_get_data(req); /* body of http msg */
	const char *action = NULL;
	size_t action_len = 0;
	const char *replyname = NULL; /* argument name for the reply */
	struct wpabuf *reply = NULL; /* data for the reply */

	if (os_strcasecmp(filename, UPNP_WPS_DEVICE_CONTROL_FILE)) {
		wpa_printf(MSG_INFO, "WPS UPnP: Invalid POST filename %s",
			   filename);
		ret = HTTP_NOT_FOUND;
		goto bad;
	}

	ret = UPNP_INVALID_ACTION;
	action = web_get_action(req, &action_len);
	if (action == NULL)
		goto bad;

	if (!os_strncasecmp("GetDeviceInfo", action, action_len))
		ret = web_process_get_device_info(sm, &reply, &replyname);
	else if (!os_strncasecmp("PutMessage", action, action_len))
		ret = web_process_put_message(sm, data, &reply, &replyname);
	else if (!os_strncasecmp("PutWLANResponse", action, action_len))
		ret = web_process_put_wlan_response(sm, data, &reply,
						    &replyname);
	else if (!os_strncasecmp("SetSelectedRegistrar", action, action_len))
		ret = web_process_set_selected_registrar(sm, cli, data, &reply,
							 &replyname);
	else
		wpa_printf(MSG_INFO, "WPS UPnP: Unknown POST type");

bad:
	if (ret != HTTP_OK)
		wpa_printf(MSG_INFO, "WPS UPnP: POST failure ret=%d", ret);
	web_connection_send_reply(req, ret, action, action_len, reply,
				  replyname);
	wpabuf_free(reply);
}