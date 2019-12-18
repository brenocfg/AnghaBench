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
 int /*<<< orphan*/  test_kevent_vnode_add () ; 
 int /*<<< orphan*/  test_kevent_vnode_del () ; 
 int /*<<< orphan*/  test_kevent_vnode_disable_and_enable () ; 
 int /*<<< orphan*/  test_kevent_vnode_dispatch () ; 
 int /*<<< orphan*/  test_kevent_vnode_note_attrib () ; 
 int /*<<< orphan*/  test_kevent_vnode_note_delete () ; 
 int /*<<< orphan*/  test_kevent_vnode_note_rename () ; 
 int /*<<< orphan*/  test_kevent_vnode_note_write () ; 

void
test_evfilt_vnode()
{
    kqfd = kqueue();
    test_kevent_vnode_add();
    test_kevent_vnode_del();
    test_kevent_vnode_disable_and_enable();
#if HAVE_EV_DISPATCH
    test_kevent_vnode_dispatch();
#endif
    test_kevent_vnode_note_write();
    test_kevent_vnode_note_attrib();
    test_kevent_vnode_note_rename();
    test_kevent_vnode_note_delete();
    close(kqfd);
}