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
typedef  int /*<<< orphan*/  evutil_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  event_base_loopexit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  global_base ; 
 int test_ok ; 

__attribute__((used)) static void
periodic_timeout_cb(evutil_socket_t fd, short event, void *arg)
{
	int *count = arg;

	(*count)++;
	if (*count == 6) {
		/* call loopexit only once - on slow machines(?), it is
		 * apparently possible for this to get called twice. */
		test_ok = 1;
		event_base_loopexit(global_base, NULL);
	}
}