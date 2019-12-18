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
struct evhttp_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  event_base_loopexit (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tt_assert (int) ; 

__attribute__((used)) static void
http_failed_request_done(struct evhttp_request *req, void *arg)
{
	tt_assert(!req);
end:
	event_base_loopexit(arg, NULL);
}