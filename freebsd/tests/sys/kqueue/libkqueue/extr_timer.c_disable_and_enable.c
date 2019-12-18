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
struct kevent {int flags; int data; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVFILT_TIMER ; 
 int EV_ADD ; 
 int EV_CLEAR ; 
 int EV_DISABLE ; 
 int EV_ENABLE ; 
 int EV_ONESHOT ; 
 int /*<<< orphan*/  EV_SET (struct kevent*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 scalar_t__ kevent (int /*<<< orphan*/ ,struct kevent*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kevent_cmp (struct kevent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kevent_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kqfd ; 
 int /*<<< orphan*/  success () ; 
 int /*<<< orphan*/  test_begin (char const*) ; 
 int /*<<< orphan*/  test_no_kevents () ; 
 int /*<<< orphan*/  vnode_fd ; 

__attribute__((used)) static void
disable_and_enable(void)
{
    const char *test_id = "kevent(EVFILT_TIMER, EV_DISABLE and EV_ENABLE)";
    struct kevent kev;

    test_begin(test_id);

    test_no_kevents();

    /* Add the watch and immediately disable it */
    EV_SET(&kev, vnode_fd, EVFILT_TIMER, EV_ADD | EV_ONESHOT, 0, 2000,NULL);
    if (kevent(kqfd, &kev, 1, NULL, 0, NULL) < 0)
        err(1, "%s", test_id);
    kev.flags = EV_DISABLE;
    if (kevent(kqfd, &kev, 1, NULL, 0, NULL) < 0)
        err(1, "%s", test_id);
    test_no_kevents();

    /* Re-enable and check again */
    kev.flags = EV_ENABLE;
    if (kevent(kqfd, &kev, 1, NULL, 0, NULL) < 0)
        err(1, "%s", test_id);

    kev.flags = EV_ADD | EV_CLEAR | EV_ONESHOT;
    kev.data = 1; 
    kevent_cmp(&kev, kevent_get(kqfd));

    success();
}