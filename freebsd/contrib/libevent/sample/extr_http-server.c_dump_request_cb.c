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
struct evkeyvalq {struct evkeyval* tqh_first; } ;
struct TYPE_2__ {struct evkeyval* tqe_next; } ;
struct evkeyval {char const* key; char* value; TYPE_1__ next; } ;
struct evhttp_request {int dummy; } ;
struct evbuffer {int dummy; } ;
typedef  int /*<<< orphan*/  cbuf ;

/* Variables and functions */
#define  EVHTTP_REQ_CONNECT 136 
#define  EVHTTP_REQ_DELETE 135 
#define  EVHTTP_REQ_GET 134 
#define  EVHTTP_REQ_HEAD 133 
#define  EVHTTP_REQ_OPTIONS 132 
#define  EVHTTP_REQ_PATCH 131 
#define  EVHTTP_REQ_POST 130 
#define  EVHTTP_REQ_PUT 129 
#define  EVHTTP_REQ_TRACE 128 
 scalar_t__ evbuffer_get_length (struct evbuffer*) ; 
 int evbuffer_remove (struct evbuffer*,char*,int) ; 
 int evhttp_request_get_command (struct evhttp_request*) ; 
 struct evbuffer* evhttp_request_get_input_buffer (struct evhttp_request*) ; 
 struct evkeyvalq* evhttp_request_get_input_headers (struct evhttp_request*) ; 
 char* evhttp_request_get_uri (struct evhttp_request*) ; 
 int /*<<< orphan*/  evhttp_send_reply (struct evhttp_request*,int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fwrite (char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char const*,char*) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void
dump_request_cb(struct evhttp_request *req, void *arg)
{
	const char *cmdtype;
	struct evkeyvalq *headers;
	struct evkeyval *header;
	struct evbuffer *buf;

	switch (evhttp_request_get_command(req)) {
	case EVHTTP_REQ_GET: cmdtype = "GET"; break;
	case EVHTTP_REQ_POST: cmdtype = "POST"; break;
	case EVHTTP_REQ_HEAD: cmdtype = "HEAD"; break;
	case EVHTTP_REQ_PUT: cmdtype = "PUT"; break;
	case EVHTTP_REQ_DELETE: cmdtype = "DELETE"; break;
	case EVHTTP_REQ_OPTIONS: cmdtype = "OPTIONS"; break;
	case EVHTTP_REQ_TRACE: cmdtype = "TRACE"; break;
	case EVHTTP_REQ_CONNECT: cmdtype = "CONNECT"; break;
	case EVHTTP_REQ_PATCH: cmdtype = "PATCH"; break;
	default: cmdtype = "unknown"; break;
	}

	printf("Received a %s request for %s\nHeaders:\n",
	    cmdtype, evhttp_request_get_uri(req));

	headers = evhttp_request_get_input_headers(req);
	for (header = headers->tqh_first; header;
	    header = header->next.tqe_next) {
		printf("  %s: %s\n", header->key, header->value);
	}

	buf = evhttp_request_get_input_buffer(req);
	puts("Input data: <<<");
	while (evbuffer_get_length(buf)) {
		int n;
		char cbuf[128];
		n = evbuffer_remove(buf, cbuf, sizeof(cbuf));
		if (n > 0)
			(void) fwrite(cbuf, 1, n, stdout);
	}
	puts(">>>");

	evhttp_send_reply(req, 200, "OK", NULL);
}