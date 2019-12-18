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
struct sockaddr_in {int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_addr; } ;
struct http_client {int dummy; } ;

/* Variables and functions */
 struct http_client* http_client_addr (struct sockaddr_in*,struct wpabuf*,size_t,void (*) (void*,struct http_client*,int),void*) ; 
 char* http_client_url_parse (char const*,struct sockaddr_in*,char**) ; 
 int /*<<< orphan*/  inet_ntoa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 scalar_t__ os_strlen (char const*) ; 
 scalar_t__ os_strncmp (char const*,char*,int) ; 
 struct wpabuf* wpabuf_alloc (scalar_t__) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_printf (struct wpabuf*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct http_client * http_client_url(const char *url,
				     struct wpabuf *req, size_t max_response,
				     void (*cb)(void *ctx,
						struct http_client *c,
						enum http_client_event event),
				     void *cb_ctx)
{
	struct sockaddr_in dst;
	struct http_client *c;
	char *u, *path;
	struct wpabuf *req_buf = NULL;

	if (os_strncmp(url, "http://", 7) != 0)
		return NULL;
	u = http_client_url_parse(url, &dst, &path);
	if (u == NULL)
		return NULL;

	if (req == NULL) {
		req_buf = wpabuf_alloc(os_strlen(url) + 1000);
		if (req_buf == NULL) {
			os_free(u);
			return NULL;
		}
		req = req_buf;
		wpabuf_printf(req,
			      "GET %s HTTP/1.1\r\n"
			      "Cache-Control: no-cache\r\n"
			      "Pragma: no-cache\r\n"
			      "Accept: text/xml, application/xml\r\n"
			      "User-Agent: wpa_supplicant\r\n"
			      "Host: %s:%d\r\n"
			      "\r\n",
			      path, inet_ntoa(dst.sin_addr),
			      ntohs(dst.sin_port));
	}
	os_free(u);

	c = http_client_addr(&dst, req, max_response, cb, cb_ctx);
	if (c == NULL) {
		wpabuf_free(req_buf);
		return NULL;
	}

	return c;
}