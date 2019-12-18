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
struct TYPE_3__ {int perms; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;
struct tty {int /*<<< orphan*/  lock; TYPE_1__ pty; } ;
struct statbuf {int mode; int inode; int /*<<< orphan*/  rdev; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;
struct TYPE_4__ {struct tty** ttys; } ;

/* Variables and functions */
 int S_IFCHR ; 
 int S_IFDIR ; 
 int /*<<< orphan*/  TTY_PSEUDO_SLAVE_MAJOR ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_make (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lock (int /*<<< orphan*/ *) ; 
 TYPE_2__ pty_slave ; 
 int /*<<< orphan*/  ttys_lock ; 
 int /*<<< orphan*/  unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void devpts_stat_num(int pty_num, struct statbuf *stat) {
    if (pty_num == -1) {
        // root
        stat->mode = S_IFDIR | 0755;
        stat->inode = 1;
    } else {
        lock(&ttys_lock);
        struct tty *tty = pty_slave.ttys[pty_num];
        assert(tty != NULL);
        lock(&tty->lock);

        stat->mode = S_IFCHR | tty->pty.perms;
        stat->uid = tty->pty.uid;
        stat->gid = tty->pty.gid;
        stat->inode = pty_num + 3;
        stat->rdev = dev_make(TTY_PSEUDO_SLAVE_MAJOR, pty_num);

        unlock(&tty->lock);
        unlock(&ttys_lock);
    }
}