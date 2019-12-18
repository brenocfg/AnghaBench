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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct comm_point {scalar_t__ ssl_shake_state; int tcp_byte_count; int /*<<< orphan*/  buffer; TYPE_1__* ev; int /*<<< orphan*/  ssl; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  ev; } ;

/* Variables and functions */
 scalar_t__ EPIPE ; 
 int /*<<< orphan*/  ERR_clear_error () ; 
 int LDNS_RR_BUF_SIZE ; 
 int SSL_ERROR_SYSCALL ; 
 int SSL_ERROR_WANT_READ ; 
 int SSL_ERROR_WANT_WRITE ; 
 int SSL_ERROR_ZERO_RETURN ; 
 int /*<<< orphan*/  SSL_MODE_ENABLE_PARTIAL_WRITE ; 
 int SSL_get_error (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SSL_set_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SSL_write (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  UB_EV_WRITE ; 
 int /*<<< orphan*/  comm_point_listen_for_rw (struct comm_point*,int,int /*<<< orphan*/ ) ; 
 void* comm_ssl_shake_hs_read ; 
 scalar_t__ comm_ssl_shake_none ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_assert (int) ; 
 int /*<<< orphan*/  log_crypto_err (char*) ; 
 int /*<<< orphan*/  log_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * sldns_buffer_current (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_buffer_limit (int /*<<< orphan*/ ) ; 
 int sldns_buffer_remaining (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_buffer_set_position (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sldns_buffer_skip (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssl_handshake (struct comm_point*) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 int /*<<< orphan*/  tcp_callback_writer (struct comm_point*) ; 
 int /*<<< orphan*/  ub_winsock_tcp_wouldblock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int verbosity ; 

__attribute__((used)) static int
ssl_handle_write(struct comm_point* c)
{
#ifdef HAVE_SSL
	int r;
	if(c->ssl_shake_state != comm_ssl_shake_none) {
		if(!ssl_handshake(c))
			return 0;
		if(c->ssl_shake_state != comm_ssl_shake_none)
			return 1;
	}
	/* ignore return, if fails we may simply block */
	(void)SSL_set_mode(c->ssl, SSL_MODE_ENABLE_PARTIAL_WRITE);
	if(c->tcp_byte_count < sizeof(uint16_t)) {
		uint16_t len = htons(sldns_buffer_limit(c->buffer));
		ERR_clear_error();
		if(sizeof(uint16_t)+sldns_buffer_remaining(c->buffer) <
			LDNS_RR_BUF_SIZE) {
			/* combine the tcp length and the query for write,
			 * this emulates writev */
			uint8_t buf[LDNS_RR_BUF_SIZE];
			memmove(buf, &len, sizeof(uint16_t));
			memmove(buf+sizeof(uint16_t),
				sldns_buffer_current(c->buffer),
				sldns_buffer_remaining(c->buffer));
			r = SSL_write(c->ssl, (void*)(buf+c->tcp_byte_count),
				(int)(sizeof(uint16_t)+
				sldns_buffer_remaining(c->buffer)
				- c->tcp_byte_count));
		} else {
			r = SSL_write(c->ssl,
				(void*)(((uint8_t*)&len)+c->tcp_byte_count),
				(int)(sizeof(uint16_t)-c->tcp_byte_count));
		}
		if(r <= 0) {
			int want = SSL_get_error(c->ssl, r);
			if(want == SSL_ERROR_ZERO_RETURN) {
				return 0; /* closed */
			} else if(want == SSL_ERROR_WANT_READ) {
				c->ssl_shake_state = comm_ssl_shake_hs_read;
				comm_point_listen_for_rw(c, 1, 0);
				return 1; /* wait for read condition */
			} else if(want == SSL_ERROR_WANT_WRITE) {
				ub_winsock_tcp_wouldblock(c->ev->ev, UB_EV_WRITE);
				return 1; /* write more later */
			} else if(want == SSL_ERROR_SYSCALL) {
#ifdef EPIPE
				if(errno == EPIPE && verbosity < 2)
					return 0; /* silence 'broken pipe' */
#endif
				if(errno != 0)
					log_err("SSL_write syscall: %s",
						strerror(errno));
				return 0;
			}
			log_crypto_err("could not SSL_write");
			return 0;
		}
		c->tcp_byte_count += r;
		if(c->tcp_byte_count < sizeof(uint16_t))
			return 1;
		sldns_buffer_set_position(c->buffer, c->tcp_byte_count -
			sizeof(uint16_t));
		if(sldns_buffer_remaining(c->buffer) == 0) {
			tcp_callback_writer(c);
			return 1;
		}
	}
	log_assert(sldns_buffer_remaining(c->buffer) > 0);
	ERR_clear_error();
	r = SSL_write(c->ssl, (void*)sldns_buffer_current(c->buffer),
		(int)sldns_buffer_remaining(c->buffer));
	if(r <= 0) {
		int want = SSL_get_error(c->ssl, r);
		if(want == SSL_ERROR_ZERO_RETURN) {
			return 0; /* closed */
		} else if(want == SSL_ERROR_WANT_READ) {
			c->ssl_shake_state = comm_ssl_shake_hs_read;
			comm_point_listen_for_rw(c, 1, 0);
			return 1; /* wait for read condition */
		} else if(want == SSL_ERROR_WANT_WRITE) {
			ub_winsock_tcp_wouldblock(c->ev->ev, UB_EV_WRITE);
			return 1; /* write more later */
		} else if(want == SSL_ERROR_SYSCALL) {
#ifdef EPIPE
			if(errno == EPIPE && verbosity < 2)
				return 0; /* silence 'broken pipe' */
#endif
			if(errno != 0)
				log_err("SSL_write syscall: %s",
					strerror(errno));
			return 0;
		}
		log_crypto_err("could not SSL_write");
		return 0;
	}
	sldns_buffer_skip(c->buffer, (ssize_t)r);

	if(sldns_buffer_remaining(c->buffer) == 0) {
		tcp_callback_writer(c);
	}
	return 1;
#else
	(void)c;
	return 0;
#endif /* HAVE_SSL */
}