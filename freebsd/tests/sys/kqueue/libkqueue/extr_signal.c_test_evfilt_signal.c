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
 int /*<<< orphan*/  kqfd ; 
 int /*<<< orphan*/  kqueue () ; 
 int /*<<< orphan*/  test_kevent_signal_add () ; 
 int /*<<< orphan*/  test_kevent_signal_del () ; 
 int /*<<< orphan*/  test_kevent_signal_disable () ; 
 int /*<<< orphan*/  test_kevent_signal_enable () ; 
 int /*<<< orphan*/  test_kevent_signal_get () ; 
 int /*<<< orphan*/  test_kevent_signal_oneshot () ; 

void
test_evfilt_signal()
{
    kqfd = kqueue();
    test_kevent_signal_add();
    test_kevent_signal_del();
    test_kevent_signal_get();
    test_kevent_signal_disable();
    test_kevent_signal_enable();
    test_kevent_signal_oneshot();
    close(kqfd);
}