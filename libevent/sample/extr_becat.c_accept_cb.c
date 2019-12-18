#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int dummy; } ;
struct event_base {int dummy; } ;
struct evconnlistener {int dummy; } ;
struct context {struct bufferevent* in; struct bufferevent* out; TYPE_2__* opts; } ;
struct bufferevent {int dummy; } ;
typedef  int /*<<< orphan*/  evutil_socket_t ;
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_3__ {int /*<<< orphan*/  keep; } ;
struct TYPE_4__ {TYPE_1__ extra; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVUTIL_ASSERT (int) ; 
 int EV_READ ; 
 int EV_WRITE ; 
 int /*<<< orphan*/  be_free (struct bufferevent**) ; 
 struct bufferevent* be_new (struct context*,struct event_base*,int /*<<< orphan*/ ) ; 
 scalar_t__ bufferevent_enable (struct bufferevent*,int) ; 
 int /*<<< orphan*/  bufferevent_setcb (struct bufferevent*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct context*) ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  evconnlistener_disable (struct evconnlistener*) ; 
 struct event_base* evconnlistener_get_base (struct evconnlistener*) ; 
 int /*<<< orphan*/  evutil_format_sockaddr_port_ (struct sockaddr*,char*,int) ; 
 int /*<<< orphan*/  info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_cb ; 
 int /*<<< orphan*/  server_event_cb ; 
 int /*<<< orphan*/  write_cb ; 

__attribute__((used)) static void
accept_cb(struct evconnlistener *listener, evutil_socket_t fd,
	struct sockaddr *sa, int socklen, void *arg)
{
	char buffer[128];
	struct context *ctx = arg;
	struct bufferevent *bev = NULL;
	struct event_base *base = evconnlistener_get_base(listener);

	if (!ctx->opts->extra.keep)
		evconnlistener_disable(listener);

	info("Accepting %s (fd=%d)\n",
		evutil_format_sockaddr_port_(sa, buffer, sizeof(buffer)-1), fd);

	bev = be_new(ctx, base, fd);
	if (!bev) {
		error("Cannot make bufferevent for fd=%d\n", fd);
		goto err;
	}

	bufferevent_setcb(bev, read_cb, write_cb, server_event_cb, ctx);
	bufferevent_enable(bev, EV_READ|EV_WRITE);

	/** TODO: support multiple bevs */
	EVUTIL_ASSERT(!ctx->out);
	ctx->out = bev;

	if (bufferevent_enable(ctx->in, EV_READ)) {
		error("Cannot monitor EV_READ on input\n");
		goto err;
	}

	return;

err:
	be_free(&bev);
}