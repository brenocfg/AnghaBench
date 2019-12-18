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
struct be_conn_hostname_result {short what; int dnserr; } ;

/* Variables and functions */
 short BEV_EVENT_CONNECTED ; 
 short BEV_EVENT_ERROR ; 
 scalar_t__ EMFILE ; 
 int /*<<< orphan*/  TT_BLATHER (char*) ; 
 int /*<<< orphan*/  TT_FAIL (char*) ; 
 int /*<<< orphan*/  be_connect_hostname_base ; 
 int bufferevent_socket_get_dns_error (struct bufferevent*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  event_base_loopexit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evutil_gai_strerror (int) ; 
 int total_connected_or_failed ; 
 int total_n_accepted ; 

__attribute__((used)) static void
be_connect_hostname_event_cb(struct bufferevent *bev, short what, void *ctx)
{
	struct be_conn_hostname_result *got = ctx;

	if (got->what) {
		TT_FAIL(("Two events on one bufferevent. %d,%d",
			got->what, (int)what));
	}

	TT_BLATHER(("Got a bufferevent event %d", what));
	got->what = what;

	if ((what & BEV_EVENT_CONNECTED) || (what & BEV_EVENT_ERROR)) {
		int expected = 3;
		int r = bufferevent_socket_get_dns_error(bev);

		if (r) {
			got->dnserr = r;
			TT_BLATHER(("DNS error %d: %s", r,
				   evutil_gai_strerror(r)));
		}
		++total_connected_or_failed;
		TT_BLATHER(("Got %d connections or errors.", total_connected_or_failed));

		/** emfile test */
		if (errno == EMFILE) {
			expected = 0;
		}

		if (total_n_accepted >= expected && total_connected_or_failed >= 5)
			event_base_loopexit(be_connect_hostname_base,
			    NULL);
	}
}