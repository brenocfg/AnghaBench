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
struct evhttp_request {int /*<<< orphan*/  evcon; } ;
struct evbuffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_FORMAT ; 
 int /*<<< orphan*/  evbuffer_add_printf (struct evbuffer*,int /*<<< orphan*/ ,int,char const*,char const*) ; 
 int /*<<< orphan*/  evbuffer_free (struct evbuffer*) ; 
 struct evbuffer* evbuffer_new () ; 
 int /*<<< orphan*/  evhttp_connection_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evhttp_response_code_ (struct evhttp_request*,int,char const*) ; 
 char* evhttp_response_phrase_internal (int) ; 
 int /*<<< orphan*/  evhttp_send_page_ (struct evhttp_request*,struct evbuffer*) ; 

void
evhttp_send_error(struct evhttp_request *req, int error, const char *reason)
{

#define ERR_FORMAT "<HTML><HEAD>\n" \
	    "<TITLE>%d %s</TITLE>\n" \
	    "</HEAD><BODY>\n" \
	    "<H1>%s</H1>\n" \
	    "</BODY></HTML>\n"

	struct evbuffer *buf = evbuffer_new();
	if (buf == NULL) {
		/* if we cannot allocate memory; we just drop the connection */
		evhttp_connection_free(req->evcon);
		return;
	}
	if (reason == NULL) {
		reason = evhttp_response_phrase_internal(error);
	}

	evhttp_response_code_(req, error, reason);

	evbuffer_add_printf(buf, ERR_FORMAT, error, reason, reason);

	evhttp_send_page_(req, buf);

	evbuffer_free(buf);
#undef ERR_FORMAT
}