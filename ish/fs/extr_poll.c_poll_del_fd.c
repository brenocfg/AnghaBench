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
struct poll_fd {int /*<<< orphan*/  fds; int /*<<< orphan*/  polls; } ;
struct poll {int /*<<< orphan*/  lock; } ;
struct fd {int /*<<< orphan*/  poll_lock; } ;

/* Variables and functions */
 int _ENOENT ; 
 int /*<<< orphan*/  free (struct poll_fd*) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock (int /*<<< orphan*/ *) ; 
 struct poll_fd* poll_find_fd (struct poll*,struct fd*) ; 
 int /*<<< orphan*/  unlock (int /*<<< orphan*/ *) ; 

int poll_del_fd(struct poll *poll, struct fd *fd) {
    int err;
    lock(&fd->poll_lock);
    lock(&poll->lock);
    struct poll_fd *poll_fd = poll_find_fd(poll, fd);
    if (poll_fd == NULL) {
        err = _ENOENT;
        goto out;
    }

    list_remove(&poll_fd->polls);
    list_remove(&poll_fd->fds);
    free(poll_fd);

    err = 0;
out:
    unlock(&poll->lock);
    unlock(&fd->poll_lock);
    return err;
}