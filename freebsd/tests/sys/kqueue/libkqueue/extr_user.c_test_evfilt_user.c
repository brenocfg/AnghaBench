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
 int /*<<< orphan*/  add_and_delete () ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_and_enable () ; 
 int /*<<< orphan*/  event_wait () ; 
 int /*<<< orphan*/  kqfd ; 
 int /*<<< orphan*/  kqueue () ; 
 int /*<<< orphan*/  oneshot () ; 

void
test_evfilt_user()
{
    kqfd = kqueue();

    add_and_delete();
    event_wait();
    disable_and_enable();
    oneshot();
    /* TODO: try different fflags operations */

    close(kqfd);
}