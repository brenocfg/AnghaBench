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
struct tty_driver {int /*<<< orphan*/  limit; int /*<<< orphan*/  ttys; } ;
struct tty {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  limit; int /*<<< orphan*/  ttys; } ;

/* Variables and functions */
 struct tty* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct tty*) ; 
 int MAX_PTYS ; 
 int /*<<< orphan*/  TTY_PSEUDO_SLAVE_MAJOR ; 
 int /*<<< orphan*/  _ENOSPC ; 
 int pty_reserve_next () ; 
 TYPE_1__ pty_slave ; 
 int /*<<< orphan*/  pty_slave_init_inode (struct tty*) ; 
 struct tty* tty_get (struct tty_driver*,int /*<<< orphan*/ ,int) ; 

struct tty *pty_open_fake(struct tty_driver *driver) {
    int pty_num = pty_reserve_next();
    if (pty_num == MAX_PTYS)
        return ERR_PTR(_ENOSPC);
    // TODO this is a bit of a hack
    driver->ttys = pty_slave.ttys;
    driver->limit = pty_slave.limit;
    struct tty *tty = tty_get(driver, TTY_PSEUDO_SLAVE_MAJOR, pty_num);
    if (IS_ERR(tty))
        return tty;
    pty_slave_init_inode(tty);
    return tty;
}