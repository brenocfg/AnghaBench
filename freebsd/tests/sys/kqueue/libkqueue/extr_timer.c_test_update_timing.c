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
 int /*<<< orphan*/  EV_SET (struct kevent*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,long,int /*<<< orphan*/ *) ; 
 int MAX_SLEEP ; 
 int MIN_SLEEP ; 
 long MS_TO_US (int) ; 
 int /*<<< orphan*/  NOTE_USECONDS ; 
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 int /*<<< orphan*/  errx (int,char*,long) ; 
 scalar_t__ kevent (int /*<<< orphan*/ ,struct kevent*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kevent_cmp (struct kevent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kevent_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kqfd ; 
 int /*<<< orphan*/  mssleep (int) ; 
 long now () ; 
 int /*<<< orphan*/  success () ; 
 int /*<<< orphan*/  test_begin (char const*) ; 
 int /*<<< orphan*/  test_no_kevents () ; 
 int /*<<< orphan*/  test_no_kevents_quietly () ; 
 int /*<<< orphan*/  ussleep (int) ; 
 int /*<<< orphan*/  vnode_fd ; 

__attribute__((used)) static void
test_update_timing(void)
{
#define	MIN_SLEEP 500
#define	MAX_SLEEP 1500
    const char *test_id = "kevent(EVFILT_TIMER (UPDATE TIMING), EV_ADD | EV_ONESHOT)";
    struct kevent kev;
    int iteration;
    int sleeptime;
    long elapsed;
    long start;
    long stop;

    test_begin(test_id);

    test_no_kevents();

    /* Re-try the update tests with a variety of delays between the
     * original timer activation and the update of the timer. The goal
     * is to show that in all cases the only timer event that is
     * received is from the update and not the original timer add.
     */
    for (sleeptime = MIN_SLEEP, iteration = 1;
         sleeptime < MAX_SLEEP;
         ++sleeptime, ++iteration) {

        /* First set the timer to 1 ms */
        EV_SET(&kev, vnode_fd, EVFILT_TIMER, EV_ADD | EV_ONESHOT,
            NOTE_USECONDS, MS_TO_US(1), NULL);
        if (kevent(kqfd, &kev, 1, NULL, 0, NULL) < 0)
            err(1, "%s", test_id);

        /* Delay; the delay ranges from less than to greater than the
         * timer period.
         */
        ussleep(sleeptime);
    
        /* Now re-add the timer with the same parameters */
        start = now();
        if (kevent(kqfd, &kev, 1, NULL, 0, NULL) < 0)
            err(1, "%s", test_id);

        /* Wait for the event */
        kev.flags |= EV_CLEAR;
        kev.fflags &= ~NOTE_USECONDS;
        kev.data = 1;
        kevent_cmp(&kev, kevent_get(kqfd));
        stop = now();
        elapsed = stop - start;

        /* Check that the timer expired after at least 1 ms. This
         * check is to make sure that the timer re-started and that
         * the event is not from the original add of the timer.
         */
        if (elapsed < MS_TO_US(1))
            errx(1, "early timer expiration: %ld us", elapsed);

        /* Make sure the re-added timer does not fire. In other words,
         * test that the event received above was the only event from
         * the add and re-add of the timer.
         */
        mssleep(2);
        test_no_kevents_quietly();
    }

    success();
}