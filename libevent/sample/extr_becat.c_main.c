#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int dummy; } ;
struct TYPE_6__ {char* port; int /*<<< orphan*/  address; } ;
struct TYPE_5__ {char* port; int /*<<< orphan*/  address; } ;
struct TYPE_4__ {scalar_t__ listen; scalar_t__ ssl; } ;
struct options {int max_read; TYPE_3__ dst; TYPE_2__ src; TYPE_1__ extra; } ;
struct event_base {int dummy; } ;
struct event {int dummy; } ;
struct evconnlistener {int dummy; } ;
struct context {int /*<<< orphan*/  ssl; struct bufferevent* out; struct bufferevent* in; int /*<<< orphan*/  fout; struct options* opts; } ;
struct bufferevent {int dummy; } ;
typedef  scalar_t__ ev_socklen_t ;
typedef  int /*<<< orphan*/  ctx ;
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/  WSADATA ;
typedef  int /*<<< orphan*/  WORD ;

/* Variables and functions */
 int EV_READ ; 
 int EV_WRITE ; 
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int LEV_OPT_CLOSE_ON_EXEC ; 
 int LEV_OPT_CLOSE_ON_FREE ; 
 int LEV_OPT_REUSEABLE ; 
 int /*<<< orphan*/  MAKEWORD (int,int) ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGPIPE ; 
 scalar_t__ SIG_ERR ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  WSACleanup () ; 
 int /*<<< orphan*/  WSAStartup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  accept_cb ; 
 int /*<<< orphan*/  be_free (struct bufferevent**) ; 
 struct bufferevent* be_new (struct context*,struct event_base*,int) ; 
 int /*<<< orphan*/  bufferevent_disable (struct bufferevent*,int) ; 
 scalar_t__ bufferevent_enable (struct bufferevent*,int) ; 
 scalar_t__ bufferevent_set_max_single_read (struct bufferevent*,int) ; 
 int /*<<< orphan*/  bufferevent_setcb (struct bufferevent*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct context*) ; 
 scalar_t__ bufferevent_socket_connect (struct bufferevent*,struct sockaddr*,scalar_t__) ; 
 struct bufferevent* bufferevent_socket_new (struct event_base*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  client_event_cb ; 
 int /*<<< orphan*/  do_term ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  evconnlistener_free (struct evconnlistener*) ; 
 struct evconnlistener* evconnlistener_new_bind (struct event_base*,int /*<<< orphan*/ ,struct context*,int,int,struct sockaddr*,scalar_t__) ; 
 scalar_t__ event_add (struct event*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_base_dispatch (struct event_base*) ; 
 int /*<<< orphan*/  event_base_free (struct event_base*) ; 
 struct event_base* event_base_new () ; 
 int /*<<< orphan*/  event_free (struct event*) ; 
 struct event* evsignal_new (struct event_base*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct event_base*) ; 
 int /*<<< orphan*/  evutil_format_sockaddr_port_ (struct sockaddr*,char*,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_event_cb ; 
 int /*<<< orphan*/  info (char*,...) ; 
 scalar_t__ make_address (struct sockaddr_storage*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (struct context*,int /*<<< orphan*/ ,int) ; 
 struct options parse_opts (int,char**) ; 
 int /*<<< orphan*/  read_cb ; 
 scalar_t__ signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssl_ctx_free (int /*<<< orphan*/ *) ; 
 scalar_t__ ssl_ctx_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  trigger_bev_write_cb ; 
 int /*<<< orphan*/ * write_cb ; 

int main(int argc, char **argv)
{
	struct event_base *base = NULL;
	struct event *term = NULL;
	struct evconnlistener *listener = NULL;
	struct bufferevent *bev = NULL;
	struct sockaddr_storage ss;
	struct sockaddr *sa = (struct sockaddr *)&ss;
	ev_socklen_t ss_len;
	char buffer[128];

	struct context ctx;
	struct options o = parse_opts(argc, argv);
	int err = EXIT_SUCCESS;

	memset(&ctx, 0, sizeof(ctx));
	ctx.opts = &o;

	base = event_base_new();
	if (!base)
		goto err;

	term = evsignal_new(base, SIGINT, do_term, base);
	if (!term)
		goto err;
	if (event_add(term, NULL))
		goto err;

#ifdef _WIN32
	{
		WORD wVersionRequested;
		WSADATA wsaData;
		wVersionRequested = MAKEWORD(2, 2);
		WSAStartup(wVersionRequested, &wsaData);
	}
#else
	if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
		goto err;
#endif

	if (o.extra.ssl && ssl_ctx_init(&ctx.ssl))
		goto err;

	if (o.extra.listen) {
		int flags = 0;
		flags |= LEV_OPT_CLOSE_ON_FREE;
		flags |= LEV_OPT_CLOSE_ON_EXEC;
		flags |= LEV_OPT_REUSEABLE;

		ss_len = make_address(&ss, o.src.address, o.src.port);
		if (!ss_len) {
			error("Cannot make address from %s:%d\n",
				o.src.address, o.src.port);
			goto err;
		}
		info("Listening on %s\n",
			evutil_format_sockaddr_port_(sa, buffer, sizeof(buffer)-1));
		listener = evconnlistener_new_bind(base, accept_cb, &ctx, flags, -1, sa, ss_len);
		if (!listener) {
			error("Cannot listen\n");
			goto err;
		}
	} else {
		ss_len = make_address(&ss, o.dst.address, o.dst.port);
		if (!ss_len) {
			error("Cannot make address from %s:%d\n",
				o.src.address, o.src.port);
			goto err;
		}
		info("Connecting to %s\n",
			evutil_format_sockaddr_port_(sa, buffer, sizeof(buffer)-1));

		bev = be_new(&ctx, base, -1);
		if (!bev) {
			error("Cannot make bufferevent\n");
			goto err;
		}

		bufferevent_setcb(bev, read_cb, write_cb, client_event_cb, &ctx);
		if (bufferevent_enable(bev, EV_READ|EV_WRITE)) {
			error("Cannot monitor EV_READ|EV_WRITE for client\n");
			goto err;
		}

		if (bufferevent_socket_connect(bev, sa, ss_len)) {
			info("Connection failed\n");
			goto err;
		}
	}

	ctx.out = bev;
	ctx.fout = stdout;

	ctx.in = bufferevent_socket_new(base, STDIN_FILENO, 0);
	if (o.max_read != -1) {
		if (bufferevent_set_max_single_read(ctx.in, o.max_read))
			goto err;
	}
	if (!ctx.in) {
		error("Cannot create input bufferevent\n");
		goto err;
	}
	bufferevent_setcb(ctx.in, trigger_bev_write_cb, NULL, in_event_cb, &ctx);
	if (ctx.out && bufferevent_enable(ctx.in, EV_READ)) {
		error("Cannot monitor EV_READ on input\n");
		goto err;
	}
	bufferevent_disable(ctx.in, EV_WRITE);

	if (!event_base_dispatch(base))
		goto out;

err:
	if (!err)
		err = EXIT_FAILURE;

out:
	if (term)
		event_free(term);
	be_free(&ctx.in);
	be_free(&ctx.out);
	if (listener)
		evconnlistener_free(listener);
	if (base)
		event_base_free(base);

	free(o.src.address);
	free(o.dst.address);

	ssl_ctx_free(&ctx.ssl);

#ifdef _WIN32
	WSACleanup();
#endif

	return err;
}