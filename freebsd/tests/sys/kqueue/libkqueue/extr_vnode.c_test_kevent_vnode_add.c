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
struct kevent {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVFILT_VNODE ; 
 int /*<<< orphan*/  EV_ADD ; 
 int /*<<< orphan*/  EV_SET (struct kevent*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int NOTE_ATTRIB ; 
 int NOTE_DELETE ; 
 int NOTE_RENAME ; 
 int NOTE_WRITE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 scalar_t__ kevent (int /*<<< orphan*/ ,struct kevent*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kqfd ; 
 scalar_t__ open (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,scalar_t__) ; 
 int /*<<< orphan*/  success () ; 
 int /*<<< orphan*/  system (char*) ; 
 int /*<<< orphan*/  test_begin (char const*) ; 
 scalar_t__ vnode_fd ; 

void
test_kevent_vnode_add(void)
{
    const char *test_id = "kevent(EVFILT_VNODE, EV_ADD)";
    const char *testfile = "./kqueue-test.tmp";
    struct kevent kev;

    test_begin(test_id);

    system("touch ./kqueue-test.tmp");
    vnode_fd = open(testfile, O_RDONLY);
    if (vnode_fd < 0)
        err(1, "open of %s", testfile);
    else
        printf("vnode_fd = %d\n", vnode_fd);

    EV_SET(&kev, vnode_fd, EVFILT_VNODE, EV_ADD, 
            NOTE_WRITE | NOTE_ATTRIB | NOTE_RENAME | NOTE_DELETE, 0, NULL);
    if (kevent(kqfd, &kev, 1, NULL, 0, NULL) < 0)
        err(1, "%s", test_id);

    success();
}