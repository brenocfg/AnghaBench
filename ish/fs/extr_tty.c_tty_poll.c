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
struct TYPE_2__ {int lflags; } ;
struct tty {scalar_t__ bufsize; scalar_t__ packet_flags; int /*<<< orphan*/  lock; int /*<<< orphan*/ * driver; TYPE_1__ termios; scalar_t__ hung_up; } ;
struct fd {struct tty* tty; } ;

/* Variables and functions */
 int ICANON_ ; 
 int POLL_ERR ; 
 int POLL_HUP ; 
 int POLL_PRI ; 
 int POLL_READ ; 
 int POLL_WRITE ; 
 int /*<<< orphan*/  lock (int /*<<< orphan*/ *) ; 
 scalar_t__ pty_is_half_closed_master (struct tty*) ; 
 int /*<<< orphan*/  pty_master ; 
 size_t tty_canon_size (struct tty*) ; 
 int /*<<< orphan*/  unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tty_poll(struct fd *fd) {
    struct tty *tty = fd->tty;
    lock(&tty->lock);
    int types = 0;
    types |= POLL_WRITE; // FIXME now that we have ptys, you can't always write without blocking
    if (tty->hung_up) {
        types |= POLL_READ | POLL_WRITE | POLL_ERR | POLL_HUP;
    } else if (pty_is_half_closed_master(tty)) {
        types |= POLL_READ | POLL_HUP;
    } else if (tty->termios.lflags & ICANON_) {
        if (tty_canon_size(tty) != (size_t) -1)
            types |= POLL_READ;
    } else {
        if (tty->bufsize > 0)
            types |= POLL_READ;
    }
    if (tty->driver == &pty_master && tty->packet_flags != 0)
        types |= POLL_PRI;
    unlock(&tty->lock);
    return types;
}