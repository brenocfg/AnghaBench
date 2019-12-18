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
struct common_timeout_info {int count; int /*<<< orphan*/  ev; int /*<<< orphan*/  called_at; } ;
typedef  int /*<<< orphan*/  evutil_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  event_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evutil_gettimeofday (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
common_timeout_cb(evutil_socket_t fd, short event, void *arg)
{
	struct common_timeout_info *ti = arg;
	++ti->count;
	evutil_gettimeofday(&ti->called_at, NULL);
	if (ti->count >= 4)
		event_del(&ti->ev);
}