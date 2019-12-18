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
struct evbuffer_iovec {scalar_t__ iov_len; int /*<<< orphan*/  iov_base; } ;
struct evbuffer {int dummy; } ;
struct bufferevent {struct evbuffer* output; } ;
struct TYPE_2__ {scalar_t__ write_suspended; struct bufferevent bev; } ;
struct bufferevent_openssl {int last_write; scalar_t__ underlying; scalar_t__ write_blocked_on_read; int /*<<< orphan*/  ssl; TYPE_1__ bev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEV_EVENT_WRITING ; 
 int /*<<< orphan*/  BEV_OPT_DEFER_CALLBACKS ; 
 int /*<<< orphan*/  BEV_RESET_GENERIC_WRITE_TIMEOUT (struct bufferevent*) ; 
 int /*<<< orphan*/  ERR_clear_error () ; 
 int /*<<< orphan*/  EV_WRITE ; 
 int OP_BLOCKED ; 
 int OP_ERR ; 
 int OP_MADE_PROGRESS ; 
#define  SSL_ERROR_WANT_READ 129 
#define  SSL_ERROR_WANT_WRITE 128 
 int SSL_get_error (int /*<<< orphan*/ ,int) ; 
 int SSL_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int bufferevent_get_write_max_ (TYPE_1__*) ; 
 int /*<<< orphan*/  bufferevent_trigger_nolock_ (struct bufferevent*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ clear_wbor (struct bufferevent_openssl*) ; 
 int /*<<< orphan*/  conn_closed (struct bufferevent_openssl*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  decrement_buckets (struct bufferevent_openssl*) ; 
 int /*<<< orphan*/  evbuffer_drain (struct evbuffer*,int) ; 
 int evbuffer_peek (struct evbuffer*,int,int /*<<< orphan*/ *,struct evbuffer_iovec*,int) ; 
 int /*<<< orphan*/  print_err (int) ; 
 int /*<<< orphan*/  set_wbor (struct bufferevent_openssl*) ; 

__attribute__((used)) static int
do_write(struct bufferevent_openssl *bev_ssl, int atmost)
{
	int i, r, n, n_written = 0;
	struct bufferevent *bev = &bev_ssl->bev.bev;
	struct evbuffer *output = bev->output;
	struct evbuffer_iovec space[8];
	int result = 0;

	if (bev_ssl->last_write > 0)
		atmost = bev_ssl->last_write;
	else
		atmost = bufferevent_get_write_max_(&bev_ssl->bev);

	n = evbuffer_peek(output, atmost, NULL, space, 8);
	if (n < 0)
		return OP_ERR | result;

	if (n > 8)
		n = 8;
	for (i=0; i < n; ++i) {
		if (bev_ssl->bev.write_suspended)
			break;

		/* SSL_write will (reasonably) return 0 if we tell it to
		   send 0 data.  Skip this case so we don't interpret the
		   result as an error */
		if (space[i].iov_len == 0)
			continue;

		ERR_clear_error();
		r = SSL_write(bev_ssl->ssl, space[i].iov_base,
		    space[i].iov_len);
		if (r > 0) {
			result |= OP_MADE_PROGRESS;
			if (bev_ssl->write_blocked_on_read)
				if (clear_wbor(bev_ssl) < 0)
					return OP_ERR | result;
			n_written += r;
			bev_ssl->last_write = -1;
			decrement_buckets(bev_ssl);
		} else {
			int err = SSL_get_error(bev_ssl->ssl, r);
			print_err(err);
			switch (err) {
			case SSL_ERROR_WANT_WRITE:
				/* Can't read until underlying has more data. */
				if (bev_ssl->write_blocked_on_read)
					if (clear_wbor(bev_ssl) < 0)
						return OP_ERR | result;
				bev_ssl->last_write = space[i].iov_len;
				break;
			case SSL_ERROR_WANT_READ:
				/* This read operation requires a write, and the
				 * underlying is full */
				if (!bev_ssl->write_blocked_on_read)
					if (set_wbor(bev_ssl) < 0)
						return OP_ERR | result;
				bev_ssl->last_write = space[i].iov_len;
				break;
			default:
				conn_closed(bev_ssl, BEV_EVENT_WRITING, err, r);
				bev_ssl->last_write = -1;
				break;
			}
			result |= OP_BLOCKED;
			break;
		}
	}
	if (n_written) {
		evbuffer_drain(output, n_written);
		if (bev_ssl->underlying)
			BEV_RESET_GENERIC_WRITE_TIMEOUT(bev);

		bufferevent_trigger_nolock_(bev, EV_WRITE, BEV_OPT_DEFER_CALLBACKS);
	}
	return result;
}