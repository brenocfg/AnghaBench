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
struct gaic_request_status {scalar_t__ magic; int canceled; int /*<<< orphan*/  base; int /*<<< orphan*/  request; } ;
typedef  int /*<<< orphan*/  evutil_socket_t ;

/* Variables and functions */
 scalar_t__ GAIC_MAGIC ; 
 int /*<<< orphan*/  evdns_getaddrinfo_cancel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_base_loopexit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tt_assert (int) ; 

__attribute__((used)) static void
gaic_cancel_request_cb(evutil_socket_t fd, short what, void *arg)
{
	struct gaic_request_status *status = arg;

	tt_assert(status->magic == GAIC_MAGIC);
	status->canceled = 1;
	evdns_getaddrinfo_cancel(status->request);
	return;
end:
	event_base_loopexit(status->base, NULL);
}