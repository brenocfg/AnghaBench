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
struct comm_point {int /*<<< orphan*/  buffer; int /*<<< orphan*/  ssl_shake_state; int /*<<< orphan*/  ssl; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 scalar_t__ ECONNRESET ; 
 int /*<<< orphan*/  ERR_clear_error () ; 
 int SSL_ERROR_SYSCALL ; 
 int SSL_ERROR_WANT_READ ; 
 int SSL_ERROR_WANT_WRITE ; 
 int SSL_ERROR_ZERO_RETURN ; 
 int SSL_get_error (int /*<<< orphan*/ ,int) ; 
 int SSL_read (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  comm_point_listen_for_rw (struct comm_point*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  comm_ssl_shake_hs_write ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  log_assert (int) ; 
 int /*<<< orphan*/  log_crypto_err (char*) ; 
 int /*<<< orphan*/  log_err (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ sldns_buffer_current (int /*<<< orphan*/ ) ; 
 scalar_t__ sldns_buffer_remaining (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_buffer_skip (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 int verbosity ; 

__attribute__((used)) static int
ssl_http_read_more(struct comm_point* c)
{
#ifdef HAVE_SSL
	int r;
	log_assert(sldns_buffer_remaining(c->buffer) > 0);
	ERR_clear_error();
	r = SSL_read(c->ssl, (void*)sldns_buffer_current(c->buffer),
		(int)sldns_buffer_remaining(c->buffer));
	if(r <= 0) {
		int want = SSL_get_error(c->ssl, r);
		if(want == SSL_ERROR_ZERO_RETURN) {
			return 0; /* shutdown, closed */
		} else if(want == SSL_ERROR_WANT_READ) {
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
	return 1;
#else
	(void)c;
	return 0;
#endif /* HAVE_SSL */
}