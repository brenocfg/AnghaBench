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
typedef  scalar_t__ time_t ;
struct kevent {int flags; int data; scalar_t__ fflags; } ;
typedef  int /*<<< orphan*/  intmax_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVFILT_TIMER ; 
 int EV_ADD ; 
 int EV_ONESHOT ; 
 int /*<<< orphan*/  EV_SET (struct kevent*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,scalar_t__,int /*<<< orphan*/ *) ; 
 int NOTE_ABSTIME ; 
 int NOTE_SECONDS ; 
 int /*<<< orphan*/  err (int,char*,char const*,...) ; 
 scalar_t__ kevent (int /*<<< orphan*/ ,struct kevent*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kevent_cmp (struct kevent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kevent_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kqfd ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  success () ; 
 int /*<<< orphan*/  test_begin (char const*) ; 
 int /*<<< orphan*/  test_no_kevents () ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnode_fd ; 

__attribute__((used)) static void
test_abstime(void)
{
    const char *test_id = "kevent(EVFILT_TIMER, EV_ONESHOT, NOTE_ABSTIME)";
    struct kevent kev;
    time_t start;
    time_t stop;
    const int timeout = 3;

    test_begin(test_id);

    test_no_kevents();

    start = time(NULL);
    EV_SET(&kev, vnode_fd, EVFILT_TIMER, EV_ADD | EV_ONESHOT,
      NOTE_ABSTIME | NOTE_SECONDS, start + timeout, NULL);
    if (kevent(kqfd, &kev, 1, NULL, 0, NULL) < 0)
        err(1, "%s", test_id);

    /* Retrieve the event */
    kev.flags = EV_ADD | EV_ONESHOT;
    kev.data = 1;
    kev.fflags = 0;
    kevent_cmp(&kev, kevent_get(kqfd));
    stop = time(NULL);
    if (stop < start + timeout)
        err(1, "too early %jd %jd", (intmax_t)stop, (intmax_t)(start + timeout));

    /* Check if the event occurs again */
    sleep(3);
    test_no_kevents();

    success();
}