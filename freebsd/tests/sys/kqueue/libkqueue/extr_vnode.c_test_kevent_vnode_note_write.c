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
struct kevent {int /*<<< orphan*/  fflags; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVFILT_VNODE ; 
 int EV_ADD ; 
 int /*<<< orphan*/  EV_ENABLE ; 
 int EV_ONESHOT ; 
 int /*<<< orphan*/  EV_SET (struct kevent*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NOTE_EXTEND ; 
 int /*<<< orphan*/  NOTE_WRITE ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 scalar_t__ kevent (int /*<<< orphan*/ ,struct kevent*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kevent_cmp (struct kevent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kevent_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kqfd ; 
 int /*<<< orphan*/  success () ; 
 scalar_t__ system (char*) ; 
 int /*<<< orphan*/  test_begin (char const*) ; 
 int /*<<< orphan*/  vnode_fd ; 

void
test_kevent_vnode_note_write(void)
{
    const char *test_id = "kevent(EVFILT_VNODE, NOTE_WRITE)";
    struct kevent kev;

    test_begin(test_id);

    EV_SET(&kev, vnode_fd, EVFILT_VNODE, EV_ADD | EV_ONESHOT, NOTE_WRITE, 0, NULL);
    if (kevent(kqfd, &kev, 1, NULL, 0, NULL) < 0)
        err(1, "%s", test_id);

    if (system("echo hello >> ./kqueue-test.tmp") < 0)
        err(1, "system");

    /* BSD kqueue adds NOTE_EXTEND even though it was not requested */
    /* BSD kqueue removes EV_ENABLE */
    kev.flags &= ~EV_ENABLE; // XXX-FIXME compatibility issue
    kev.fflags |= NOTE_EXTEND; // XXX-FIXME compatibility issue
    kevent_cmp(&kev, kevent_get(kqfd));

    success();
}