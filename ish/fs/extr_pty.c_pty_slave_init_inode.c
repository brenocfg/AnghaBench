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
struct tty {TYPE_1__ pty; } ;
struct TYPE_4__ {int /*<<< orphan*/  egid; int /*<<< orphan*/  euid; } ;

/* Variables and functions */
 TYPE_2__* current ; 

__attribute__((used)) static void pty_slave_init_inode(struct tty *tty) {
    tty->pty.uid = current->euid;
    // TODO make these mount options
    tty->pty.gid = current->egid;
    tty->pty.perms = 0620;
}