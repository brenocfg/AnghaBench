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
struct fd {TYPE_1__* tty; int /*<<< orphan*/  tty_other_fds; } ;
struct TYPE_2__ {int /*<<< orphan*/  fds_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_remove_safe (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_release (TYPE_1__*) ; 
 int /*<<< orphan*/  ttys_lock ; 
 int /*<<< orphan*/  unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tty_close(struct fd *fd) {
    if (fd->tty != NULL) {
        lock(&fd->tty->fds_lock);
        list_remove_safe(&fd->tty_other_fds);
        unlock(&fd->tty->fds_lock);
        lock(&ttys_lock);
        tty_release(fd->tty);
        unlock(&ttys_lock);
    }
    return 0;
}