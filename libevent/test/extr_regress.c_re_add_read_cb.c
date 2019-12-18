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
struct event {int dummy; } ;
typedef  int /*<<< orphan*/  evutil_socket_t ;
typedef  scalar_t__ ev_ssize_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  event_add (struct event*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_base_loopbreak (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_get_base (struct event*) ; 
 scalar_t__ read (int /*<<< orphan*/ ,char*,int) ; 
 struct event* readd_test_event_last_added ; 
 int /*<<< orphan*/  test_ok ; 
 int /*<<< orphan*/  tt_fail_perror (char*) ; 

__attribute__((used)) static void
re_add_read_cb(evutil_socket_t fd, short event, void *arg)
{
	char buf[256];
	struct event *ev_other = arg;
	ev_ssize_t n_read;

	readd_test_event_last_added = ev_other;

	n_read = read(fd, buf, sizeof(buf));

	if (n_read < 0) {
		tt_fail_perror("read");
		event_base_loopbreak(event_get_base(ev_other));
	} else {
		event_add(ev_other, NULL);
		++test_ok;
	}
}