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
struct upnp_wps_device_sm {int dummy; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_addr; } ;
struct http_request {int dummy; } ;
typedef  enum httpread_hdr_type { ____Placeholder_httpread_hdr_type } httpread_hdr_type ;

/* Variables and functions */
#define  HTTPREAD_HDR_TYPE_GET 131 
#define  HTTPREAD_HDR_TYPE_POST 130 
#define  HTTPREAD_HDR_TYPE_SUBSCRIBE 129 
#define  HTTPREAD_HDR_TYPE_UNSUBSCRIBE 128 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  http_request_deinit (struct http_request*) ; 
 struct sockaddr_in* http_request_get_cli_addr (struct http_request*) ; 
 int http_request_get_type (struct http_request*) ; 
 char* http_request_get_uri (struct http_request*) ; 
 int /*<<< orphan*/  inet_ntoa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  web_connection_parse_get (struct upnp_wps_device_sm*,struct http_request*,char*) ; 
 int /*<<< orphan*/  web_connection_parse_post (struct upnp_wps_device_sm*,struct sockaddr_in*,struct http_request*,char*) ; 
 int /*<<< orphan*/  web_connection_parse_subscribe (struct upnp_wps_device_sm*,struct http_request*,char*) ; 
 int /*<<< orphan*/  web_connection_parse_unsubscribe (struct upnp_wps_device_sm*,struct http_request*,char*) ; 
 int /*<<< orphan*/  web_connection_unimplemented (struct http_request*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void web_connection_check_data(void *ctx, struct http_request *req)
{
	struct upnp_wps_device_sm *sm = ctx;
	enum httpread_hdr_type htype = http_request_get_type(req);
	char *filename = http_request_get_uri(req);
	struct sockaddr_in *cli = http_request_get_cli_addr(req);

	if (!filename) {
		wpa_printf(MSG_INFO, "WPS UPnP: Could not get HTTP URI");
		http_request_deinit(req);
		return;
	}
	/* Trim leading slashes from filename */
	while (*filename == '/')
		filename++;

	wpa_printf(MSG_DEBUG, "WPS UPnP: Got HTTP request type %d from %s:%d",
		   htype, inet_ntoa(cli->sin_addr), htons(cli->sin_port));

	switch (htype) {
	case HTTPREAD_HDR_TYPE_GET:
		web_connection_parse_get(sm, req, filename);
		break;
	case HTTPREAD_HDR_TYPE_POST:
		web_connection_parse_post(sm, cli, req, filename);
		break;
	case HTTPREAD_HDR_TYPE_SUBSCRIBE:
		web_connection_parse_subscribe(sm, req, filename);
		break;
	case HTTPREAD_HDR_TYPE_UNSUBSCRIBE:
		web_connection_parse_unsubscribe(sm, req, filename);
		break;

		/* We are not required to support M-POST; just plain
		 * POST is supposed to work, so we only support that.
		 * If for some reason we need to support M-POST, it is
		 * mostly the same as POST, with small differences.
		 */
	default:
		/* Send 501 for anything else */
		web_connection_unimplemented(req);
		break;
	}
}