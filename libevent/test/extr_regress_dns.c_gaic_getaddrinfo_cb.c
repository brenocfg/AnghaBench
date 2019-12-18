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
struct gaic_request_status {scalar_t__ magic; int canceled; int /*<<< orphan*/  cancel_event; struct event_base* base; } ;
struct evutil_addrinfo {int dummy; } ;
struct event_base {int dummy; } ;

/* Variables and functions */
 int EVUTIL_EAI_CANCEL ; 
 scalar_t__ GAIC_MAGIC ; 
 int /*<<< orphan*/  event_base_loopexit (struct event_base*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct gaic_request_status*) ; 
 int /*<<< orphan*/  memset (struct gaic_request_status*,int,int) ; 
 scalar_t__ pending ; 
 int /*<<< orphan*/  tt_assert (int) ; 

__attribute__((used)) static void
gaic_getaddrinfo_cb(int result, struct evutil_addrinfo *res, void *arg)
{
	struct gaic_request_status *status = arg;
	struct event_base *base = status->base;
	tt_assert(status->magic == GAIC_MAGIC);

	if (result == EVUTIL_EAI_CANCEL) {
		tt_assert(status->canceled);
	}
	event_del(&status->cancel_event);

	memset(status, 0xf0, sizeof(*status));
	free(status);

end:
	if (--pending <= 0)
		event_base_loopexit(base, NULL);
}