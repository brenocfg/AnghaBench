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

/* Variables and functions */
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_and_enable () ; 
 int /*<<< orphan*/  kqfd ; 
 int /*<<< orphan*/  kqueue () ; 
 int /*<<< orphan*/  test_abstime () ; 
 int /*<<< orphan*/  test_kevent_timer_add () ; 
 int /*<<< orphan*/  test_kevent_timer_del () ; 
 int /*<<< orphan*/  test_kevent_timer_get () ; 
 int /*<<< orphan*/  test_oneshot () ; 
 int /*<<< orphan*/  test_periodic () ; 
 int /*<<< orphan*/  test_update () ; 
 int /*<<< orphan*/  test_update_equal () ; 
 int /*<<< orphan*/  test_update_expired () ; 
 int /*<<< orphan*/  test_update_periodic () ; 
 int /*<<< orphan*/  test_update_timing () ; 

void
test_evfilt_timer()
{
    kqfd = kqueue();
    test_kevent_timer_add();
    test_kevent_timer_del();
    test_kevent_timer_get();
    test_oneshot();
    test_periodic();
    test_abstime();
    test_update();
    test_update_equal();
    test_update_expired();
    test_update_timing();
    test_update_periodic();
    disable_and_enable();
    close(kqfd);
}