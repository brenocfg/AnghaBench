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
typedef  int /*<<< orphan*/  uint16_t ;
struct comm_point {scalar_t__ ssl_shake_state; int tcp_byte_count; int /*<<< orphan*/  buffer; TYPE_1__* ev; scalar_t__ tcp_req_info; int /*<<< orphan*/  ssl; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  ev; } ;

/* Variables and functions */
 scalar_t__ ECONNRESET ; 
 int /*<<< orphan*/  ERR_clear_error () ; 
 scalar_t__ LDNS_HEADER_SIZE ; 
 int SSL_ERROR_SYSCALL ; 
 int SSL_ERROR_WANT_READ ; 
 int SSL_ERROR_WANT_WRITE ; 
 int SSL_ERROR_ZERO_RETURN ; 
 int SSL_get_error (int /*<<< orphan*/ ,int) ; 
 int SSL_read (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  UB_EV_READ ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  VERB_QUERY ; 
 int /*<<< orphan*/  comm_point_listen_for_rw (struct comm_point*,int /*<<< orphan*/ ,int) ; 
 void* comm_ssl_shake_hs_write ; 
 scalar_t__ comm_ssl_shake_none ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  log_crypto_err (char*) ; 
 int /*<<< orphan*/  log_err (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ sldns_buffer_at (int /*<<< orphan*/ ,int) ; 
 scalar_t__ sldns_buffer_capacity (int /*<<< orphan*/ ) ; 
 scalar_t__ sldns_buffer_current (int /*<<< orphan*/ ) ; 
 scalar_t__ sldns_buffer_limit (int /*<<< orphan*/ ) ; 
 scalar_t__ sldns_buffer_read_u16_at (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sldns_buffer_remaining (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_buffer_set_limit (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sldns_buffer_skip (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssl_handshake (struct comm_point*) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 int /*<<< orphan*/  tcp_callback_reader (struct comm_point*) ; 
 int tcp_req_info_handle_read_close (scalar_t__) ; 
 int /*<<< orphan*/  ub_winsock_tcp_wouldblock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,...) ; 
 int verbosity ; 

__attribute__((used)) static int
ssl_handle_read(struct comm_point* c)
{
#ifdef HAVE_SSL
	int r;
	if(c->ssl_shake_state != comm_ssl_shake_none) {
		if(!ssl_handshake(c))
			return 0;
		if(c->ssl_shake_state != comm_ssl_shake_none)
			return 1;
	}
	if(c->tcp_byte_count < sizeof(uint16_t)) {
		/* read length bytes */
		ERR_clear_error();
		if((r=SSL_read(c->ssl, (void*)sldns_buffer_at(c->buffer,
			c->tcp_byte_count), (int)(sizeof(uint16_t) -
			c->tcp_byte_count))) <= 0) {
			int want = SSL_get_error(c->ssl, r);
			if(want == SSL_ERROR_ZERO_RETURN) {
				if(c->tcp_req_info)
					return tcp_req_info_handle_read_close(c->tcp_req_info);
				return 0; /* shutdown, closed */
			} else if(want == SSL_ERROR_WANT_READ) {
				ub_winsock_tcp_wouldblock(c->ev->ev, UB_EV_READ);
				return 1; /* read more later */
			} else if(want == SSL_ERROR_WANT_WRITE) {
				c->ssl_shake_state = comm_ssl_shake_hs_write;
				comm_point_listen_for_rw(c, 0, 1);
				return 1;
			} else if(want == SSL_ERROR_SYSCALL) {
#ifdef ECONNRESET
				if(errno == ECONNRESET && verbosity < 2)
					return 0; /* silence reset by peer */
#endif
				if(errno != 0)
					log_err("SSL_read syscall: %s",
						strerror(errno));
				return 0;
			}
			log_crypto_err("could not SSL_read");
			return 0;
		}
		c->tcp_byte_count += r;
		if(c->tcp_byte_count < sizeof(uint16_t))
			return 1;
		if(sldns_buffer_read_u16_at(c->buffer, 0) >
			sldns_buffer_capacity(c->buffer)) {
			verbose(VERB_QUERY, "ssl: dropped larger than buffer");
			return 0;
		}
		sldns_buffer_set_limit(c->buffer,
			sldns_buffer_read_u16_at(c->buffer, 0));
		if(sldns_buffer_limit(c->buffer) < LDNS_HEADER_SIZE) {
			verbose(VERB_QUERY, "ssl: dropped bogus too short.");
			return 0;
		}
		sldns_buffer_skip(c->buffer, (ssize_t)(c->tcp_byte_count-sizeof(uint16_t)));
		verbose(VERB_ALGO, "Reading ssl tcp query of length %d",
			(int)sldns_buffer_limit(c->buffer));
	}
	if(sldns_buffer_remaining(c->buffer) > 0) {
		ERR_clear_error();
		r = SSL_read(c->ssl, (void*)sldns_buffer_current(c->buffer),
			(int)sldns_buffer_remaining(c->buffer));
		if(r <= 0) {
			int want = SSL_get_error(c->ssl, r);
			if(want == SSL_ERROR_ZERO_RETURN) {
				if(c->tcp_req_info)
					return tcp_req_info_handle_read_close(c->tcp_req_info);
				return 0; /* shutdown, closed */
			} else if(want == SSL_ERROR_WANT_READ) {
				ub_winsock_tcp_wouldblock(c->ev->ev, UB_EV_READ);
				return 1; /* read more later */
			} else if(want == SSL_ERROR_WANT_WRITE) {
				c->ssl_shake_state = comm_ssl_shake_hs_write;
				comm_point_listen_for_rw(c, 0, 1);
				return 1;
			} else if(want == SSL_ERROR_SYSCALL) {
#ifdef ECONNRESET
				if(errno == ECONNRESET && verbosity < 2)
					return 0; /* silence reset by peer */
#endif
				if(errno != 0)
					log_err("SSL_read syscall: %s",
						strerror(errno));
				return 0;
			}
			log_crypto_err("could not SSL_read");
			return 0;
		}
		sldns_buffer_skip(c->buffer, (ssize_t)r);
	}
	if(sldns_buffer_remaining(c->buffer) <= 0) {
		tcp_callback_reader(c);
	}
	return 1;
#else
	(void)c;
	return 0;
#endif /* HAVE_SSL */
}