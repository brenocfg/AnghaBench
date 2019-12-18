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
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 short BEV_EVENT_CONNECTED ; 
 short BEV_EVENT_EOF ; 
 short BEV_EVENT_ERROR ; 
 int /*<<< orphan*/ * SSL_get_peer_certificate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TT_BLATHER (char*) ; 
 int /*<<< orphan*/  bufferevent_free (struct bufferevent*) ; 
 int /*<<< orphan*/ * bufferevent_openssl_get_ssl (struct bufferevent*) ; 
 int /*<<< orphan*/  event_base_loopexit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit_base ; 
 int /*<<< orphan*/  got_close ; 
 int /*<<< orphan*/  got_error ; 
 int /*<<< orphan*/  n_connected ; 
 scalar_t__ pending_connect_events ; 
 scalar_t__ stop_when_connected ; 
 scalar_t__ strcmp (void*,char*) ; 
 int /*<<< orphan*/  tt_assert (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
eventcb(struct bufferevent *bev, short what, void *ctx)
{
	TT_BLATHER(("Got event %d", (int)what));
	if (what & BEV_EVENT_CONNECTED) {
		SSL *ssl;
		X509 *peer_cert;
		++n_connected;
		ssl = bufferevent_openssl_get_ssl(bev);
		tt_assert(ssl);
		peer_cert = SSL_get_peer_certificate(ssl);
		if (0==strcmp(ctx, "server")) {
			tt_assert(peer_cert == NULL);
		} else {
			tt_assert(peer_cert != NULL);
		}
		if (stop_when_connected) {
			if (--pending_connect_events == 0)
				event_base_loopexit(exit_base, NULL);
		}
	} else if (what & BEV_EVENT_EOF) {
		TT_BLATHER(("Got a good EOF"));
		++got_close;
		bufferevent_free(bev);
	} else if (what & BEV_EVENT_ERROR) {
		TT_BLATHER(("Got an error."));
		++got_error;
		bufferevent_free(bev);
	}
end:
	;
}