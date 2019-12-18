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
struct TYPE_2__ {scalar_t__ expirations; } ;
struct fd {int flags; int /*<<< orphan*/  lock; TYPE_1__ timerfd; int /*<<< orphan*/  cond; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int O_NONBLOCK_ ; 
 int _EAGAIN ; 
 int _EINVAL ; 
 int /*<<< orphan*/  lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t timerfd_read(struct fd *fd, void *buf, size_t bufsize) {
    if (bufsize < sizeof(uint64_t))
        return _EINVAL;
    lock(&fd->lock);
    while (fd->timerfd.expirations == 0) {
        if (fd->flags & O_NONBLOCK_) {
            unlock(&fd->lock);
            return _EAGAIN;
        }
        wait_for(&fd->cond, &fd->lock, NULL);
    }

    *(uint64_t *) buf = fd->timerfd.expirations;
    fd->timerfd.expirations = 0;
    unlock(&fd->lock);
    return sizeof(uint64_t);
}