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
struct evbuffer_iovec {int iov_len; int /*<<< orphan*/  iov_base; } ;
struct evbuffer {int dummy; } ;
struct bufferevent {struct evbuffer* input; } ;
struct TYPE_2__ {scalar_t__ read_suspended; struct bufferevent bev; } ;
struct bufferevent_openssl {scalar_t__ underlying; scalar_t__ read_blocked_on_write; int /*<<< orphan*/  ssl; TYPE_1__ bev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEV_EVENT_READING ; 
 int /*<<< orphan*/  BEV_RESET_GENERIC_READ_TIMEOUT (struct bufferevent*) ; 
 int OP_BLOCKED ; 
 int OP_ERR ; 
 int OP_MADE_PROGRESS ; 
#define  SSL_ERROR_WANT_READ 129 
#define  SSL_ERROR_WANT_WRITE 128 
 int SSL_get_error (int /*<<< orphan*/ ,int) ; 
 int SSL_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int bufferevent_get_read_max_ (TYPE_1__*) ; 
 scalar_t__ clear_rbow (struct bufferevent_openssl*) ; 
 int /*<<< orphan*/  conn_closed (struct bufferevent_openssl*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  decrement_buckets (struct bufferevent_openssl*) ; 
 int /*<<< orphan*/  evbuffer_commit_space (struct evbuffer*,struct evbuffer_iovec*,int) ; 
 int evbuffer_reserve_space (struct evbuffer*,int,struct evbuffer_iovec*,int) ; 
 int /*<<< orphan*/  print_err (int) ; 
 int /*<<< orphan*/  set_rbow (struct bufferevent_openssl*) ; 

__attribute__((used)) static int
do_read(struct bufferevent_openssl *bev_ssl, int n_to_read) {
	/* Requires lock */
	struct bufferevent *bev = &bev_ssl->bev.bev;
	struct evbuffer *input = bev->input;
	int r, n, i, n_used = 0, atmost;
	struct evbuffer_iovec space[2];
	int result = 0;

	if (bev_ssl->bev.read_suspended)
		return 0;

	atmost = bufferevent_get_read_max_(&bev_ssl->bev);
	if (n_to_read > atmost)
		n_to_read = atmost;

	n = evbuffer_reserve_space(input, n_to_read, space, 2);
	if (n < 0)
		return OP_ERR;

	for (i=0; i<n; ++i) {
		if (bev_ssl->bev.read_suspended)
			break;
		r = SSL_read(bev_ssl->ssl, space[i].iov_base, space[i].iov_len);
		if (r>0) {
			result |= OP_MADE_PROGRESS;
			if (bev_ssl->read_blocked_on_write)
				if (clear_rbow(bev_ssl) < 0)
					return OP_ERR | result;
			++n_used;
			space[i].iov_len = r;
			decrement_buckets(bev_ssl);
		} else {
			int err = SSL_get_error(bev_ssl->ssl, r);
			print_err(err);
			switch (err) {
			case SSL_ERROR_WANT_READ:
				/* Can't read until underlying has more data. */
				if (bev_ssl->read_blocked_on_write)
					if (clear_rbow(bev_ssl) < 0)
						return OP_ERR | result;
				break;
			case SSL_ERROR_WANT_WRITE:
				/* This read operation requires a write, and the
				 * underlying is full */
				if (!bev_ssl->read_blocked_on_write)
					if (set_rbow(bev_ssl) < 0)
						return OP_ERR | result;
				break;
			default:
				conn_closed(bev_ssl, BEV_EVENT_READING, err, r);
				break;
			}
			result |= OP_BLOCKED;
			break; /* out of the loop */
		}
	}

	if (n_used) {
		evbuffer_commit_space(input, space, n_used);
		if (bev_ssl->underlying)
			BEV_RESET_GENERIC_READ_TIMEOUT(bev);
	}

	return result;
}