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
struct tty_driver {int /*<<< orphan*/ ** ttys; TYPE_1__* ops; } ;
struct TYPE_4__ {struct tty* other; } ;
struct tty {scalar_t__ refcount; size_t num; int /*<<< orphan*/  lock; TYPE_2__ pty; struct tty_driver* driver; int /*<<< orphan*/  produced; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* cleanup ) (struct tty*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct tty*) ; 
 int /*<<< orphan*/  lock (int /*<<< orphan*/ *) ; 
 struct tty_driver pty_slave ; 
 int /*<<< orphan*/  stub1 (struct tty*) ; 
 int /*<<< orphan*/  tty_poll_wakeup (struct tty*) ; 
 int /*<<< orphan*/  unlock (int /*<<< orphan*/ *) ; 

void tty_release(struct tty *tty) {
    lock(&tty->lock);
    if (--tty->refcount == 0) {
        struct tty_driver *driver = tty->driver;
        if (driver->ops->cleanup)
            driver->ops->cleanup(tty);
        driver->ttys[tty->num] = NULL;
        unlock(&tty->lock);
        cond_destroy(&tty->produced);
        free(tty);
    } else {
        // bit of a hack
        struct tty *master = NULL;
        if (tty->driver == &pty_slave && tty->refcount == 1)
            master = tty->pty.other;
        unlock(&tty->lock);
        if (master != NULL) {
            lock(&master->lock);
            tty_poll_wakeup(master);
            unlock(&master->lock);
        }
    }
}