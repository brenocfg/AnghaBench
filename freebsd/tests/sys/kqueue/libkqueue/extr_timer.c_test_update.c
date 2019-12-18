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
struct kevent {int data; int /*<<< orphan*/  fflags; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVFILT_TIMER ; 
 int EV_ADD ; 
 int /*<<< orphan*/  EV_CLEAR ; 
 int EV_ONESHOT ; 
 int /*<<< orphan*/  EV_SET (struct kevent*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,long,void*) ; 
 long MS_TO_US (int) ; 
 int /*<<< orphan*/  NOTE_USECONDS ; 
 long SEC_TO_US (int) ; 
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 int /*<<< orphan*/  errx (int,char*,long) ; 
 scalar_t__ kevent (int /*<<< orphan*/ ,struct kevent*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kevent_cmp (struct kevent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kevent_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kqfd ; 
 long now () ; 
 int /*<<< orphan*/  printf (char*,long) ; 
 int /*<<< orphan*/  success () ; 
 int /*<<< orphan*/  test_begin (char const*) ; 
 int /*<<< orphan*/  test_no_kevents () ; 
 int /*<<< orphan*/  vnode_fd ; 

__attribute__((used)) static void
test_update(void)
{
    const char *test_id = "kevent(EVFILT_TIMER (UPDATE), EV_ADD | EV_ONESHOT)";
    struct kevent kev;
    long elapsed;
    long start;

    test_begin(test_id);

    test_no_kevents();

    /* First set the timer to 1 second */
    EV_SET(&kev, vnode_fd, EVFILT_TIMER, EV_ADD | EV_ONESHOT,
        NOTE_USECONDS, SEC_TO_US(1), (void *)1);
    start = now();
    if (kevent(kqfd, &kev, 1, NULL, 0, NULL) < 0)
        err(1, "%s", test_id);

    /* Now reduce the timer to 1 ms */
    EV_SET(&kev, vnode_fd, EVFILT_TIMER, EV_ADD | EV_ONESHOT,
        NOTE_USECONDS, MS_TO_US(1), (void *)2);
    if (kevent(kqfd, &kev, 1, NULL, 0, NULL) < 0)
        err(1, "%s", test_id);

    /* Wait for the event */
    kev.flags |= EV_CLEAR;
    kev.fflags &= ~NOTE_USECONDS;
    kev.data = 1;
    kevent_cmp(&kev, kevent_get(kqfd));
    elapsed = now() - start;

    /* Check that the timer expired after at least 1 ms, but less than
     * 1 second. This check is to make sure that the original 1 second
     * timeout was not used.
     */
    printf("timer expired after %ld us\n", elapsed);
    if (elapsed < MS_TO_US(1))
        errx(1, "early timer expiration: %ld us", elapsed);
    if (elapsed > SEC_TO_US(1))
        errx(1, "late timer expiration: %ld us", elapsed);

    success();
}