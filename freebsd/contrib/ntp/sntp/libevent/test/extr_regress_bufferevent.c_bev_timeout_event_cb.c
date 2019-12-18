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
struct timeout_cb_result {int /*<<< orphan*/  n_write_timeouts; int /*<<< orphan*/  write_timeout_at; int /*<<< orphan*/  n_read_timeouts; int /*<<< orphan*/  read_timeout_at; int /*<<< orphan*/  total_calls; } ;
struct bufferevent {int dummy; } ;

/* Variables and functions */
 short BEV_EVENT_READING ; 
 short BEV_EVENT_TIMEOUT ; 
 short BEV_EVENT_WRITING ; 
 int /*<<< orphan*/  evutil_gettimeofday (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bev_timeout_event_cb(struct bufferevent *bev, short what, void *arg)
{
	struct timeout_cb_result *res = arg;
	++res->total_calls;

	if ((what & (BEV_EVENT_READING|BEV_EVENT_TIMEOUT))
	    == (BEV_EVENT_READING|BEV_EVENT_TIMEOUT)) {
		evutil_gettimeofday(&res->read_timeout_at, NULL);
		++res->n_read_timeouts;
	}
	if ((what & (BEV_EVENT_WRITING|BEV_EVENT_TIMEOUT))
	    == (BEV_EVENT_WRITING|BEV_EVENT_TIMEOUT)) {
		evutil_gettimeofday(&res->write_timeout_at, NULL);
		++res->n_write_timeouts;
	}
}