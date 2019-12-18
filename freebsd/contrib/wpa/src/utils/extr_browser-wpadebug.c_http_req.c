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
struct browser_data {int success; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 int atoi (char const*) ; 
 int /*<<< orphan*/  browser_timeout ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eloop_register_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct browser_data**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eloop_terminate () ; 
 int /*<<< orphan*/  http_request_deinit (struct http_request*) ; 
 char* http_request_get_uri (struct http_request*) ; 
 int /*<<< orphan*/  http_request_send_and_deinit (struct http_request*,struct wpabuf*) ; 
 scalar_t__ os_strcmp (char const*,char*) ; 
 scalar_t__ os_strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,char const*) ; 
 struct wpabuf* wpabuf_alloc (int) ; 
 int /*<<< orphan*/  wpabuf_put_str (struct wpabuf*,char*) ; 

__attribute__((used)) static void http_req(void *ctx, struct http_request *req)
{
	struct browser_data *data = ctx;
	struct wpabuf *resp;
	const char *url;
	int done = 0;

	url = http_request_get_uri(req);
	wpa_printf(MSG_INFO, "Browser response received: %s", url);

	if (os_strcmp(url, "/") == 0) {
		data->success = 1;
		done = 1;
	} else if (os_strncmp(url, "/osu/", 5) == 0) {
		data->success = atoi(url + 5);
		done = 1;
	}

	resp = wpabuf_alloc(100);
	if (resp == NULL) {
		http_request_deinit(req);
		if (done)
			eloop_terminate();
		return;
	}
	wpabuf_put_str(resp, "HTTP/1.1\r\n\r\nUser input completed");

	if (done) {
		eloop_cancel_timeout(browser_timeout, NULL, NULL);
		eloop_register_timeout(0, 500000, browser_timeout, &data, NULL);
	}

	http_request_send_and_deinit(req, resp);
}