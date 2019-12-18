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
struct timeout_cb_result {int /*<<< orphan*/  last_read_at; } ;
struct bufferevent {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  evutil_gettimeofday (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bev_timeout_read_cb(struct bufferevent *bev, void *arg)
{
	struct timeout_cb_result *res = arg;
	evutil_gettimeofday(&res->last_read_at, NULL);
}