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
struct event_iocp_port {int dummy; } ;
struct event_base {int dummy; } ;
struct bufferevent {void* output; void* input; } ;
struct TYPE_2__ {struct bufferevent bev; } ;
struct bufferevent_async {int ok; TYPE_1__ bev; int /*<<< orphan*/  write_overlapped; int /*<<< orphan*/  read_overlapped; int /*<<< orphan*/  connect_overlapped; } ;
typedef  int /*<<< orphan*/  evutil_socket_t ;

/* Variables and functions */
 int BEV_OPT_THREADSAFE ; 
 int ERROR_INVALID_PARAMETER ; 
 int GetLastError () ; 
 int /*<<< orphan*/  be_async_inbuf_callback ; 
 int /*<<< orphan*/  be_async_outbuf_callback ; 
 int /*<<< orphan*/  bufferevent_free (struct bufferevent*) ; 
 scalar_t__ bufferevent_init_common_ (TYPE_1__*,struct event_base*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bufferevent_init_generic_timeout_cbs_ (struct bufferevent*) ; 
 int /*<<< orphan*/  bufferevent_ops_async ; 
 int /*<<< orphan*/  connect_complete ; 
 int /*<<< orphan*/  evbuffer_add_cb (void*,int /*<<< orphan*/ ,struct bufferevent*) ; 
 int /*<<< orphan*/  evbuffer_free (void*) ; 
 void* evbuffer_overlapped_new_ (int /*<<< orphan*/ ) ; 
 struct event_iocp_port* event_base_get_iocp_ (struct event_base*) ; 
 scalar_t__ event_iocp_port_associate_ (struct event_iocp_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  event_overlapped_init_ (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct bufferevent_async* mm_calloc (int,int) ; 
 int /*<<< orphan*/  mm_free (struct bufferevent_async*) ; 
 int /*<<< orphan*/  read_complete ; 
 int /*<<< orphan*/  write_complete ; 

struct bufferevent *
bufferevent_async_new_(struct event_base *base,
    evutil_socket_t fd, int options)
{
	struct bufferevent_async *bev_a;
	struct bufferevent *bev;
	struct event_iocp_port *iocp;

	options |= BEV_OPT_THREADSAFE;

	if (!(iocp = event_base_get_iocp_(base)))
		return NULL;

	if (fd >= 0 && event_iocp_port_associate_(iocp, fd, 1)<0) {
		int err = GetLastError();
		/* We may have alrady associated this fd with a port.
		 * Let's hope it's this port, and that the error code
		 * for doing this neer changes. */
		if (err != ERROR_INVALID_PARAMETER)
			return NULL;
	}

	if (!(bev_a = mm_calloc(1, sizeof(struct bufferevent_async))))
		return NULL;

	bev = &bev_a->bev.bev;
	if (!(bev->input = evbuffer_overlapped_new_(fd))) {
		mm_free(bev_a);
		return NULL;
	}
	if (!(bev->output = evbuffer_overlapped_new_(fd))) {
		evbuffer_free(bev->input);
		mm_free(bev_a);
		return NULL;
	}

	if (bufferevent_init_common_(&bev_a->bev, base, &bufferevent_ops_async,
		options)<0)
		goto err;

	evbuffer_add_cb(bev->input, be_async_inbuf_callback, bev);
	evbuffer_add_cb(bev->output, be_async_outbuf_callback, bev);

	event_overlapped_init_(&bev_a->connect_overlapped, connect_complete);
	event_overlapped_init_(&bev_a->read_overlapped, read_complete);
	event_overlapped_init_(&bev_a->write_overlapped, write_complete);

	bufferevent_init_generic_timeout_cbs_(bev);

	bev_a->ok = fd >= 0;

	return bev;
err:
	bufferevent_free(&bev_a->bev.bev);
	return NULL;
}