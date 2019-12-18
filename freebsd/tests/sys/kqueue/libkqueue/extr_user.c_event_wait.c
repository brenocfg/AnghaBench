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
struct kevent {int flags; int /*<<< orphan*/  fflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVFILT_USER ; 
 int EV_ADD ; 
 int EV_CLEAR ; 
 int /*<<< orphan*/  NOTE_FFCTRLMASK ; 
 int /*<<< orphan*/  NOTE_TRIGGER ; 
 int /*<<< orphan*/  kevent_add (int /*<<< orphan*/ ,struct kevent*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kevent_cmp (struct kevent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kevent_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kqfd ; 
 int /*<<< orphan*/  success () ; 
 int /*<<< orphan*/  test_begin (char const*) ; 
 int /*<<< orphan*/  test_no_kevents () ; 

__attribute__((used)) static void
event_wait(void)
{
    const char *test_id = "kevent(EVFILT_USER, wait)";
    struct kevent kev;

    test_begin(test_id);

    test_no_kevents();

    /* Add the event, and then trigger it */
    kevent_add(kqfd, &kev, 1, EVFILT_USER, EV_ADD | EV_CLEAR, 0, 0, NULL);    
    kevent_add(kqfd, &kev, 1, EVFILT_USER, 0, NOTE_TRIGGER, 0, NULL);    

    kev.fflags &= ~NOTE_FFCTRLMASK;
    kev.fflags &= ~NOTE_TRIGGER;
    kev.flags = EV_CLEAR;
    kevent_cmp(&kev, kevent_get(kqfd));

    test_no_kevents();

    success();
}