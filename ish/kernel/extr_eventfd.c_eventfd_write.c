#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_2__ {scalar_t__ val; } ;
struct fd {int flags; int /*<<< orphan*/  lock; int /*<<< orphan*/  cond; TYPE_1__ eventfd; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int O_NONBLOCK_ ; 
 scalar_t__ UINT64_MAX ; 
 int _EAGAIN ; 
 int _EINVAL ; 
 int /*<<< orphan*/  lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  notify (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poll_wakeup (struct fd*) ; 
 int /*<<< orphan*/  unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t eventfd_write(struct fd *fd, const void *buf, size_t bufsize) {
    if (bufsize < sizeof(uint64_t))
        return _EINVAL;
    uint64_t increment = *(uint64_t *) buf;
    if (increment == UINT64_MAX)
        return _EINVAL;

    lock(&fd->lock);
    while (fd->eventfd.val >= UINT64_MAX - increment) {
        if (fd->flags & O_NONBLOCK_) {
            unlock(&fd->lock);
            return _EAGAIN;
        }
        wait_for(&fd->cond, &fd->lock, NULL);
    }

    fd->eventfd.val += increment;
    notify(&fd->cond);
    unlock(&fd->lock);
    poll_wakeup(fd);
    return sizeof(uint64_t);
}