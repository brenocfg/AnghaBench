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
struct bufferevent {int dummy; } ;
typedef  enum regress_openssl_type { ____Placeholder_regress_openssl_type } regress_openssl_type ;
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 short BEV_EVENT_CONNECTED ; 
 short BEV_EVENT_EOF ; 
 short BEV_EVENT_ERROR ; 
 short BEV_EVENT_TIMEOUT ; 
 int REGRESS_OPENSSL_CLIENT ; 
 int REGRESS_OPENSSL_CLIENT_WRITE ; 
 int REGRESS_OPENSSL_FD ; 
 int REGRESS_OPENSSL_FILTER ; 
 int REGRESS_OPENSSL_FREED ; 
 int REGRESS_OPENSSL_SERVER ; 
 int /*<<< orphan*/ * SSL_get_peer_certificate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TT_BLATHER (char*) ; 
 int /*<<< orphan*/  X509_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bufferevent_free (struct bufferevent*) ; 
 int /*<<< orphan*/  bufferevent_get_output (struct bufferevent*) ; 
 int /*<<< orphan*/  bufferevent_openssl_check_fd (struct bufferevent*,int) ; 
 int /*<<< orphan*/  bufferevent_openssl_check_freed (struct bufferevent*) ; 
 int /*<<< orphan*/ * bufferevent_openssl_get_ssl (struct bufferevent*) ; 
 int /*<<< orphan*/  evbuffer_add_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  event_base_loopexit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit_base ; 
 int /*<<< orphan*/  got_close ; 
 int /*<<< orphan*/  got_error ; 
 int /*<<< orphan*/  got_timeout ; 
 int /*<<< orphan*/  n_connected ; 
 scalar_t__ pending_connect_events ; 
 scalar_t__ stop_when_connected ; 
 int /*<<< orphan*/  tt_assert (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
eventcb(struct bufferevent *bev, short what, void *ctx)
{
	X509 *peer_cert = NULL;
	enum regress_openssl_type type;

	type = (enum regress_openssl_type)ctx;

	TT_BLATHER(("Got event %d", (int)what));
	if (what & BEV_EVENT_CONNECTED) {
		SSL *ssl;
		++n_connected;
		ssl = bufferevent_openssl_get_ssl(bev);
		tt_assert(ssl);
		peer_cert = SSL_get_peer_certificate(ssl);
		if (type & REGRESS_OPENSSL_SERVER) {
			tt_assert(peer_cert == NULL);
		} else {
			tt_assert(peer_cert != NULL);
		}
		if (stop_when_connected) {
			if (--pending_connect_events == 0)
				event_base_loopexit(exit_base, NULL);
		}

		if ((type & REGRESS_OPENSSL_CLIENT_WRITE) && (type & REGRESS_OPENSSL_CLIENT))
			evbuffer_add_printf(bufferevent_get_output(bev), "1\n");
	} else if (what & BEV_EVENT_EOF) {
		TT_BLATHER(("Got a good EOF"));
		++got_close;
		if (type & REGRESS_OPENSSL_FD) {
			bufferevent_openssl_check_fd(bev, type & REGRESS_OPENSSL_FILTER);
		}
		if (type & REGRESS_OPENSSL_FREED) {
			bufferevent_openssl_check_freed(bev);
		}
		bufferevent_free(bev);
	} else if (what & BEV_EVENT_ERROR) {
		TT_BLATHER(("Got an error."));
		++got_error;
		if (type & REGRESS_OPENSSL_FD) {
			bufferevent_openssl_check_fd(bev, type & REGRESS_OPENSSL_FILTER);
		}
		if (type & REGRESS_OPENSSL_FREED) {
			bufferevent_openssl_check_freed(bev);
		}
		bufferevent_free(bev);
	} else if (what & BEV_EVENT_TIMEOUT) {
		TT_BLATHER(("Got timeout."));
		++got_timeout;
		if (type & REGRESS_OPENSSL_FD) {
			bufferevent_openssl_check_fd(bev, type & REGRESS_OPENSSL_FILTER);
		}
		if (type & REGRESS_OPENSSL_FREED) {
			bufferevent_openssl_check_freed(bev);
		}
		bufferevent_free(bev);
	}

end:
	if (peer_cert)
		X509_free(peer_cert);
}