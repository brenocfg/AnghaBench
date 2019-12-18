#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tty {scalar_t__ session; int /*<<< orphan*/  lock; int /*<<< orphan*/  fds_lock; int /*<<< orphan*/  fds; } ;
struct fd {int flags; int /*<<< orphan*/  tty_other_fds; struct tty* tty; } ;
struct TYPE_4__ {scalar_t__ pid; TYPE_1__* group; } ;
struct TYPE_3__ {scalar_t__ sid; } ;

/* Variables and functions */
 int O_NOCTTY_ ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pids_lock ; 
 int /*<<< orphan*/  tty_set_controlling (TYPE_1__*,struct tty*) ; 
 int /*<<< orphan*/  unlock (int /*<<< orphan*/ *) ; 

int tty_open(struct tty *tty, struct fd *fd) {
    fd->tty = tty;

    lock(&tty->fds_lock);
    list_add(&tty->fds, &fd->tty_other_fds);
    unlock(&tty->fds_lock);

    if (!(fd->flags & O_NOCTTY_)) {
        // Make this our controlling terminal if:
        // - the terminal doesn't already have a session
        // - we're a session leader
        lock(&pids_lock);
        lock(&tty->lock);
        if (tty->session == 0 && current->group->sid == current->pid)
            tty_set_controlling(current->group, tty);
        unlock(&tty->lock);
        unlock(&pids_lock);
    }

    return 0;
}