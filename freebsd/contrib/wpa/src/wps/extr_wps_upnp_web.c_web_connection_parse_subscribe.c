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
typedef  int /*<<< orphan*/  u8 ;
struct wpabuf {int dummy; } ;
struct upnp_wps_device_sm {int dummy; } ;
struct subscription {int /*<<< orphan*/ * uuid; } ;
struct http_request {int dummy; } ;
typedef  int /*<<< orphan*/  str ;
typedef  enum http_reply_code { ____Placeholder_http_reply_code } http_reply_code ;

/* Variables and functions */
 int HTTP_BAD_REQUEST ; 
 int HTTP_INTERNAL_SERVER_ERROR ; 
 int /*<<< orphan*/  HTTP_OK ; 
 int HTTP_PRECONDITION_FAILED ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  UPNP_SUBSCRIBE_SEC ; 
 int /*<<< orphan*/  UPNP_WPS_DEVICE_EVENT_FILE ; 
 int UUID_LEN ; 
 char* dup_binstr (char*,int) ; 
 char* http_connection_close ; 
 int /*<<< orphan*/  http_put_date (struct wpabuf*) ; 
 int /*<<< orphan*/  http_put_empty (struct wpabuf*,int) ; 
 int /*<<< orphan*/  http_put_reply_code (struct wpabuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  http_request_deinit (struct http_request*) ; 
 char* http_request_get_hdr (struct http_request*) ; 
 int /*<<< orphan*/  http_request_send_and_deinit (struct http_request*,struct wpabuf*) ; 
 char* http_server_hdr ; 
 int /*<<< orphan*/  os_free (char*) ; 
 scalar_t__ os_strcasecmp (char const*,int /*<<< orphan*/ ) ; 
 char* os_strchr (char*,char) ; 
 int os_strlen (char*) ; 
 scalar_t__ os_strncasecmp (char*,char*,int) ; 
 struct subscription* subscription_renew (struct upnp_wps_device_sm*,int /*<<< orphan*/ *) ; 
 struct subscription* subscription_start (struct upnp_wps_device_sm*,char*) ; 
 int /*<<< orphan*/  uuid_bin2str (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ uuid_str2bin (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 struct wpabuf* wpabuf_alloc (int) ; 
 int /*<<< orphan*/  wpabuf_printf (struct wpabuf*,char*,int /*<<< orphan*/ ) ; 
 char* wpabuf_put (struct wpabuf*,int) ; 
 int /*<<< orphan*/  wpabuf_put_str (struct wpabuf*,char*) ; 

__attribute__((used)) static void web_connection_parse_subscribe(struct upnp_wps_device_sm *sm,
					   struct http_request *req,
					   const char *filename)
{
	struct wpabuf *buf;
	char *b;
	char *hdr = http_request_get_hdr(req);
	char *h;
	char *match;
	int match_len;
	char *end;
	int len;
	int got_nt = 0;
	u8 uuid[UUID_LEN];
	int got_uuid = 0;
	char *callback_urls = NULL;
	struct subscription *s = NULL;
	enum http_reply_code ret = HTTP_INTERNAL_SERVER_ERROR;

	buf = wpabuf_alloc(1000);
	if (buf == NULL) {
		http_request_deinit(req);
		return;
	}

	wpa_hexdump_ascii(MSG_DEBUG, "WPS UPnP: HTTP SUBSCRIBE",
			  (u8 *) hdr, os_strlen(hdr));

	/* Parse/validate headers */
	h = hdr;
	/* First line: SUBSCRIBE /wps_event HTTP/1.1
	 * has already been parsed.
	 */
	if (os_strcasecmp(filename, UPNP_WPS_DEVICE_EVENT_FILE) != 0) {
		ret = HTTP_PRECONDITION_FAILED;
		goto error;
	}
	wpa_printf(MSG_DEBUG, "WPS UPnP: HTTP SUBSCRIBE for event");
	end = os_strchr(h, '\n');

	while (end) {
		/* Option line by option line */
		h = end + 1;
		end = os_strchr(h, '\n');
		if (end == NULL)
			break; /* no unterminated lines allowed */

		/* NT assures that it is our type of subscription;
		 * not used for a renewal.
		 **/
		match = "NT:";
		match_len = os_strlen(match);
		if (os_strncasecmp(h, match, match_len) == 0) {
			h += match_len;
			while (*h == ' ' || *h == '\t')
				h++;
			match = "upnp:event";
			match_len = os_strlen(match);
			if (os_strncasecmp(h, match, match_len) != 0) {
				ret = HTTP_BAD_REQUEST;
				goto error;
			}
			got_nt = 1;
			continue;
		}
		/* HOST should refer to us */
#if 0
		match = "HOST:";
		match_len = os_strlen(match);
		if (os_strncasecmp(h, match, match_len) == 0) {
			h += match_len;
			while (*h == ' ' || *h == '\t')
				h++;
			.....
		}
#endif
		/* CALLBACK gives one or more URLs for NOTIFYs
		 * to be sent as a result of the subscription.
		 * Each URL is enclosed in angle brackets.
		 */
		match = "CALLBACK:";
		match_len = os_strlen(match);
		if (os_strncasecmp(h, match, match_len) == 0) {
			h += match_len;
			while (*h == ' ' || *h == '\t')
				h++;
			len = end - h;
			os_free(callback_urls);
			callback_urls = dup_binstr(h, len);
			if (callback_urls == NULL) {
				ret = HTTP_INTERNAL_SERVER_ERROR;
				goto error;
			}
			if (len > 0 && callback_urls[len - 1] == '\r')
				callback_urls[len - 1] = '\0';
			continue;
		}
		/* SID is only for renewal */
		match = "SID:";
		match_len = os_strlen(match);
		if (os_strncasecmp(h, match, match_len) == 0) {
			h += match_len;
			while (*h == ' ' || *h == '\t')
				h++;
			match = "uuid:";
			match_len = os_strlen(match);
			if (os_strncasecmp(h, match, match_len) != 0) {
				ret = HTTP_BAD_REQUEST;
				goto error;
			}
			h += match_len;
			while (*h == ' ' || *h == '\t')
				h++;
			if (uuid_str2bin(h, uuid)) {
				ret = HTTP_BAD_REQUEST;
				goto error;
			}
			got_uuid = 1;
			continue;
		}
		/* TIMEOUT is requested timeout, but apparently we can
		 * just ignore this.
		 */
	}

	if (got_uuid) {
		/* renewal */
		wpa_printf(MSG_DEBUG, "WPS UPnP: Subscription renewal");
		if (callback_urls) {
			ret = HTTP_BAD_REQUEST;
			goto error;
		}
		s = subscription_renew(sm, uuid);
		if (s == NULL) {
			char str[80];
			uuid_bin2str(uuid, str, sizeof(str));
			wpa_printf(MSG_DEBUG, "WPS UPnP: Could not find "
				   "SID %s", str);
			ret = HTTP_PRECONDITION_FAILED;
			goto error;
		}
	} else if (callback_urls) {
		wpa_printf(MSG_DEBUG, "WPS UPnP: New subscription");
		if (!got_nt) {
			ret = HTTP_PRECONDITION_FAILED;
			goto error;
		}
		s = subscription_start(sm, callback_urls);
		if (s == NULL) {
			ret = HTTP_INTERNAL_SERVER_ERROR;
			goto error;
		}
	} else {
		ret = HTTP_PRECONDITION_FAILED;
		goto error;
	}

	/* success */
	http_put_reply_code(buf, HTTP_OK);
	wpabuf_put_str(buf, http_server_hdr);
	wpabuf_put_str(buf, http_connection_close);
	wpabuf_put_str(buf, "Content-Length: 0\r\n");
	wpabuf_put_str(buf, "SID: uuid:");
	/* subscription id */
	b = wpabuf_put(buf, 0);
	uuid_bin2str(s->uuid, b, 80);
	wpa_printf(MSG_DEBUG, "WPS UPnP: Assigned SID %s", b);
	wpabuf_put(buf, os_strlen(b));
	wpabuf_put_str(buf, "\r\n");
	wpabuf_printf(buf, "Timeout: Second-%d\r\n", UPNP_SUBSCRIBE_SEC);
	http_put_date(buf);
	/* And empty line to terminate header: */
	wpabuf_put_str(buf, "\r\n");

	os_free(callback_urls);
	http_request_send_and_deinit(req, buf);
	return;

error:
	/* Per UPnP spec:
	* Errors
	* Incompatible headers
	*   400 Bad Request. If SID header and one of NT or CALLBACK headers
	*     are present, the publisher must respond with HTTP error
	*     400 Bad Request.
	* Missing or invalid CALLBACK
	*   412 Precondition Failed. If CALLBACK header is missing or does not
	*     contain a valid HTTP URL, the publisher must respond with HTTP
	*     error 412 Precondition Failed.
	* Invalid NT
	*   412 Precondition Failed. If NT header does not equal upnp:event,
	*     the publisher must respond with HTTP error 412 Precondition
	*     Failed.
	* [For resubscription, use 412 if unknown uuid].
	* Unable to accept subscription
	*   5xx. If a publisher is not able to accept a subscription (such as
	*     due to insufficient resources), it must respond with a
	*     HTTP 500-series error code.
	*   599 Too many subscriptions (not a standard HTTP error)
	*/
	wpa_printf(MSG_DEBUG, "WPS UPnP: SUBSCRIBE failed - return %d", ret);
	http_put_empty(buf, ret);
	http_request_send_and_deinit(req, buf);
	os_free(callback_urls);
}