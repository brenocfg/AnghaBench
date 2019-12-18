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
struct TYPE_2__ {struct tty* other; } ;
struct tty {int /*<<< orphan*/  lock; TYPE_1__ pty; } ;

/* Variables and functions */
 int /*<<< orphan*/  lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_hangup (struct tty*) ; 
 int /*<<< orphan*/  tty_release (struct tty*) ; 
 int /*<<< orphan*/  unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pty_master_cleanup(struct tty *tty) {
    struct tty *slave = tty->pty.other;
    slave->pty.other = NULL;
    lock(&slave->lock);
    tty_hangup(slave);
    unlock(&slave->lock);
    tty_release(slave);
}