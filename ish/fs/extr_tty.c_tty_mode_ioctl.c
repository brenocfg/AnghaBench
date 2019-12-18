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
struct winsize_ {int dummy; } ;
struct termios_ {int dummy; } ;
struct TYPE_2__ {struct tty* other; } ;
struct tty {int /*<<< orphan*/  lock; int /*<<< orphan*/ * driver; struct winsize_ winsize; struct termios_ termios; int /*<<< orphan*/  consumed; int /*<<< orphan*/  bufsize; TYPE_1__ pty; } ;

/* Variables and functions */
#define  TCGETS_ 133 
#define  TCSETSF_ 132 
#define  TCSETSW_ 131 
#define  TCSETS_ 130 
#define  TIOCGWINSZ_ 129 
#define  TIOCSWINSZ_ 128 
 int _ENOTTY ; 
 int /*<<< orphan*/  lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  notify (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pty_master ; 
 int /*<<< orphan*/  tty_set_winsize (struct tty*,struct winsize_) ; 
 int /*<<< orphan*/  unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tty_mode_ioctl(struct tty *in_tty, int cmd, void *arg) {
    int err = 0;
    struct tty *tty = in_tty;
    if (in_tty->driver == &pty_master) {
        tty = in_tty->pty.other;
        lock(&tty->lock);
    }

    switch (cmd) {
        case TCGETS_:
            *(struct termios_ *) arg = tty->termios;
            break;
        case TCSETSF_:
            tty->bufsize = 0;
            notify(&tty->consumed);
        case TCSETSW_:
            // we have no output buffer currently
        case TCSETS_:
            tty->termios = *(struct termios_ *) arg;
            break;

        case TIOCGWINSZ_:
            *(struct winsize_ *) arg = tty->winsize;
            break;
        case TIOCSWINSZ_:
            tty_set_winsize(tty, *(struct winsize_ *) arg);
            break;

        default:
            err = _ENOTTY;
            break;
    }

    if (in_tty->driver == &pty_master)
        unlock(&tty->lock);
    return err;
}