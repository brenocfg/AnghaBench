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
 int /*<<< orphan*/  EVUTIL_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_base_loopexit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit_base ; 

__attribute__((used)) static void
http_request_no_action_done(struct evhttp_request *req, void *arg)
{
	EVUTIL_ASSERT(exit_base);
	event_base_loopexit(exit_base, NULL);
}