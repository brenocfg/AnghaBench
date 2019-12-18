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
struct tty {int dummy; } ;
struct fd {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct tty*) ; 
 int MAX_PTYS ; 
 int PTR_ERR (struct tty*) ; 
 int /*<<< orphan*/  TTY_PSEUDO_MASTER_MAJOR ; 
 int _ENOSPC ; 
 int /*<<< orphan*/  pty_master ; 
 int pty_reserve_next () ; 
 struct tty* tty_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int tty_open (struct tty*,struct fd*) ; 

int ptmx_open(struct fd *fd) {
    int pty_num = pty_reserve_next();
    if (pty_num == MAX_PTYS)
        return _ENOSPC;
    struct tty *master = tty_get(&pty_master, TTY_PSEUDO_MASTER_MAJOR, pty_num);
    if (IS_ERR(master))
        return PTR_ERR(master);
    return tty_open(master, fd);
}