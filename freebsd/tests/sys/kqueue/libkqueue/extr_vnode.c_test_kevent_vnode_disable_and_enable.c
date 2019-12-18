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
struct kevent {scalar_t__ ident; scalar_t__ filter; scalar_t__ fflags; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 scalar_t__ EVFILT_VNODE ; 
 int EV_ADD ; 
 int /*<<< orphan*/  EV_DISABLE ; 
 int /*<<< orphan*/  EV_ENABLE ; 
 int EV_ONESHOT ; 
 int /*<<< orphan*/  EV_SET (struct kevent*,scalar_t__,scalar_t__,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ NOTE_ATTRIB ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int kevent (int /*<<< orphan*/ ,struct kevent*,int,struct kevent*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kqfd ; 
 int /*<<< orphan*/  success () ; 
 scalar_t__ system (char*) ; 
 int /*<<< orphan*/  test_begin (char const*) ; 
 int /*<<< orphan*/  test_no_kevents () ; 
 scalar_t__ vnode_fd ; 

void
test_kevent_vnode_disable_and_enable(void)
{
    const char *test_id = "kevent(EVFILT_VNODE, EV_DISABLE and EV_ENABLE)";
    struct kevent kev;
    int nfds;

    test_begin(test_id);

    test_no_kevents();

    /* Add the watch and immediately disable it */
    EV_SET(&kev, vnode_fd, EVFILT_VNODE, EV_ADD | EV_ONESHOT, NOTE_ATTRIB, 0, NULL);
    if (kevent(kqfd, &kev, 1, NULL, 0, NULL) < 0)
        err(1, "%s", test_id);
    kev.flags = EV_DISABLE;
    if (kevent(kqfd, &kev, 1, NULL, 0, NULL) < 0)
        err(1, "%s", test_id);

    /* Confirm that the watch is disabled */
    if (system("touch ./kqueue-test.tmp") < 0)
        err(1, "system");
    test_no_kevents();

    /* Re-enable and check again */
    kev.flags = EV_ENABLE;
    if (kevent(kqfd, &kev, 1, NULL, 0, NULL) < 0)
        err(1, "%s", test_id);
    if (system("touch ./kqueue-test.tmp") < 0)
        err(1, "system");
    nfds = kevent(kqfd, NULL, 0, &kev, 1, NULL);
    if (nfds < 1)
        err(1, "%s", test_id);
    if (kev.ident != vnode_fd ||
            kev.filter != EVFILT_VNODE || 
            kev.fflags != NOTE_ATTRIB)
        err(1, "%s - incorrect event (sig=%u; filt=%d; flags=%d)", 
                test_id, (unsigned int)kev.ident, kev.filter, kev.flags);

    success();
}