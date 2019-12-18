#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct evhttp_request {int type; TYPE_1__* evcon; int /*<<< orphan*/ * uri; int /*<<< orphan*/  response_code; scalar_t__ userdone; } ;
struct evhttp_cb {int /*<<< orphan*/  cbarg; int /*<<< orphan*/  (* cb ) (struct evhttp_request*,int /*<<< orphan*/ ) ;} ;
struct evhttp {int allowed_methods; int /*<<< orphan*/  gencbarg; int /*<<< orphan*/  (* gencb ) (struct evhttp_request*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  callbacks; } ;
struct evbuffer {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  bufev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_FORMAT ; 
 int /*<<< orphan*/  EV_READ ; 
 int /*<<< orphan*/  HTTP_NOTFOUND ; 
 int /*<<< orphan*/  HTTP_NOTIMPLEMENTED ; 
 int /*<<< orphan*/  bufferevent_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evbuffer_add_printf (struct evbuffer*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  evbuffer_free (struct evbuffer*) ; 
 struct evbuffer* evbuffer_new () ; 
 int /*<<< orphan*/  event_debug (char*) ; 
 int /*<<< orphan*/  evhttp_connection_free (TYPE_1__*) ; 
 struct evhttp_cb* evhttp_dispatch_callback (int /*<<< orphan*/ *,struct evhttp_request*) ; 
 int /*<<< orphan*/  evhttp_find_vhost (struct evhttp*,struct evhttp**,char const*) ; 
 char* evhttp_htmlescape (int /*<<< orphan*/ *) ; 
 char* evhttp_request_get_host (struct evhttp_request*) ; 
 int /*<<< orphan*/  evhttp_response_code_ (struct evhttp_request*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  evhttp_send_error (struct evhttp_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evhttp_send_page_ (struct evhttp_request*,struct evbuffer*) ; 
 int /*<<< orphan*/  mm_free (char*) ; 
 int /*<<< orphan*/  stub1 (struct evhttp_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct evhttp_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
evhttp_handle_request(struct evhttp_request *req, void *arg)
{
	struct evhttp *http = arg;
	struct evhttp_cb *cb = NULL;
	const char *hostname;

	/* we have a new request on which the user needs to take action */
	req->userdone = 0;

	bufferevent_disable(req->evcon->bufev, EV_READ);

	if (req->uri == NULL) {
		evhttp_send_error(req, req->response_code, NULL);
		return;
	}

	if ((http->allowed_methods & req->type) == 0) {
		event_debug(("Rejecting disallowed method %x (allowed: %x)\n",
			(unsigned)req->type, (unsigned)http->allowed_methods));
		evhttp_send_error(req, HTTP_NOTIMPLEMENTED, NULL);
		return;
	}

	/* handle potential virtual hosts */
	hostname = evhttp_request_get_host(req);
	if (hostname != NULL) {
		evhttp_find_vhost(http, &http, hostname);
	}

	if ((cb = evhttp_dispatch_callback(&http->callbacks, req)) != NULL) {
		(*cb->cb)(req, cb->cbarg);
		return;
	}

	/* Generic call back */
	if (http->gencb) {
		(*http->gencb)(req, http->gencbarg);
		return;
	} else {
		/* We need to send a 404 here */
#define ERR_FORMAT "<html><head>" \
		    "<title>404 Not Found</title>" \
		    "</head><body>" \
		    "<h1>Not Found</h1>" \
		    "<p>The requested URL %s was not found on this server.</p>"\
		    "</body></html>\n"

		char *escaped_html;
		struct evbuffer *buf;

		if ((escaped_html = evhttp_htmlescape(req->uri)) == NULL) {
			evhttp_connection_free(req->evcon);
			return;
		}

		if ((buf = evbuffer_new()) == NULL) {
			mm_free(escaped_html);
			evhttp_connection_free(req->evcon);
			return;
		}

		evhttp_response_code_(req, HTTP_NOTFOUND, "Not Found");

		evbuffer_add_printf(buf, ERR_FORMAT, escaped_html);

		mm_free(escaped_html);

		evhttp_send_page_(req, buf);

		evbuffer_free(buf);
#undef ERR_FORMAT
	}
}