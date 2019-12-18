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
struct http_request {int dummy; } ;
typedef  int /*<<< orphan*/  len_buf ;
typedef  enum http_reply_code { ____Placeholder_http_reply_code } http_reply_code ;

/* Variables and functions */
 int HTTP_OK ; 
 int /*<<< orphan*/  MSG_INFO ; 
 scalar_t__ base64_encode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*) ; 
 char* http_connection_close ; 
 int /*<<< orphan*/  http_put_date (struct wpabuf*) ; 
 int /*<<< orphan*/  http_request_deinit (struct http_request*) ; 
 int /*<<< orphan*/  http_request_send_and_deinit (struct http_request*,struct wpabuf*) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 int /*<<< orphan*/  os_memcpy (char*,char*,unsigned int) ; 
 int /*<<< orphan*/  os_snprintf (char*,int,char*,int) ; 
 unsigned int os_strlen (char*) ; 
 char* soap_error_postfix ; 
 char* soap_error_prefix ; 
 char* soap_postfix ; 
 char* soap_prefix ; 
 char* urn_wfawlanconfig ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 struct wpabuf* wpabuf_alloc (int) ; 
 int /*<<< orphan*/  wpabuf_head (struct wpabuf const*) ; 
 int /*<<< orphan*/  wpabuf_len (struct wpabuf const*) ; 
 int /*<<< orphan*/  wpabuf_printf (struct wpabuf*,char*,...) ; 
 char* wpabuf_put (struct wpabuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_put_data (struct wpabuf*,char const*,int) ; 
 int /*<<< orphan*/  wpabuf_put_str (struct wpabuf*,char*) ; 

__attribute__((used)) static void web_connection_send_reply(struct http_request *req,
				      enum http_reply_code ret,
				      const char *action, int action_len,
				      const struct wpabuf *reply,
				      const char *replyname)
{
	struct wpabuf *buf;
	char *replydata;
	char *put_length_here = NULL;
	char *body_start = NULL;

	if (reply) {
		size_t len;
		replydata = (char *) base64_encode(wpabuf_head(reply),
						   wpabuf_len(reply), &len);
	} else
		replydata = NULL;

	/* Parameters of the response:
	 *      action(action_len) -- action we are responding to
	 *      replyname -- a name we need for the reply
	 *      replydata -- NULL or null-terminated string
	 */
	buf = wpabuf_alloc(1000 + (replydata ? os_strlen(replydata) : 0U) +
			   (action_len > 0 ? action_len * 2 : 0));
	if (buf == NULL) {
		wpa_printf(MSG_INFO, "WPS UPnP: Cannot allocate reply to "
			   "POST");
		os_free(replydata);
		http_request_deinit(req);
		return;
	}

	/*
	 * Assuming we will be successful, put in the output header first.
	 * Note: we do not keep connections alive (and httpread does
	 * not support it)... therefore we must have Connection: close.
	 */
	if (ret == HTTP_OK) {
		wpabuf_put_str(buf,
			       "HTTP/1.1 200 OK\r\n"
			       "Content-Type: text/xml; "
			       "charset=\"utf-8\"\r\n");
	} else {
		wpabuf_printf(buf, "HTTP/1.1 %d Error\r\n", ret);
	}
	wpabuf_put_str(buf, http_connection_close);

	wpabuf_put_str(buf, "Content-Length: ");
	/*
	 * We will paste the length in later, leaving some extra whitespace.
	 * HTTP code is supposed to be tolerant of extra whitespace.
	 */
	put_length_here = wpabuf_put(buf, 0);
	wpabuf_put_str(buf, "        \r\n");

	http_put_date(buf);

	/* terminating empty line */
	wpabuf_put_str(buf, "\r\n");

	body_start = wpabuf_put(buf, 0);

	if (ret == HTTP_OK) {
		wpabuf_put_str(buf, soap_prefix);
		wpabuf_put_str(buf, "<u:");
		wpabuf_put_data(buf, action, action_len);
		wpabuf_put_str(buf, "Response xmlns:u=\"");
		wpabuf_put_str(buf, urn_wfawlanconfig);
		wpabuf_put_str(buf, "\">\n");
		if (replydata && replyname) {
			/* TODO: might possibly need to escape part of reply
			 * data? ...
			 * probably not, unlikely to have ampersand(&) or left
			 * angle bracket (<) in it...
			 */
			wpabuf_printf(buf, "<%s>", replyname);
			wpabuf_put_str(buf, replydata);
			wpabuf_printf(buf, "</%s>\n", replyname);
		}
		wpabuf_put_str(buf, "</u:");
		wpabuf_put_data(buf, action, action_len);
		wpabuf_put_str(buf, "Response>\n");
		wpabuf_put_str(buf, soap_postfix);
	} else {
		/* Error case */
		wpabuf_put_str(buf, soap_prefix);
		wpabuf_put_str(buf, soap_error_prefix);
		wpabuf_printf(buf, "<errorCode>%d</errorCode>\n", ret);
		wpabuf_put_str(buf, soap_error_postfix);
		wpabuf_put_str(buf, soap_postfix);
	}
	os_free(replydata);

	/* Now patch in the content length at the end */
	if (body_start && put_length_here) {
		int body_length = (char *) wpabuf_put(buf, 0) - body_start;
		char len_buf[10];
		os_snprintf(len_buf, sizeof(len_buf), "%d", body_length);
		os_memcpy(put_length_here, len_buf, os_strlen(len_buf));
	}

	http_request_send_and_deinit(req, buf);
}