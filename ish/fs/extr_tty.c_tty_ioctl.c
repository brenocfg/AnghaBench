#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct tty {int /*<<< orphan*/  lock; TYPE_3__* driver; int /*<<< orphan*/  bufsize; int /*<<< orphan*/  fg_group; int /*<<< orphan*/  session; int /*<<< orphan*/  consumed; scalar_t__ hung_up; } ;
struct fd {struct tty* tty; } ;
typedef  int /*<<< orphan*/  pid_t_ ;
typedef  int /*<<< orphan*/  dword_t ;
struct TYPE_8__ {TYPE_1__* group; } ;
struct TYPE_7__ {TYPE_2__* ops; } ;
struct TYPE_6__ {int (* ioctl ) (struct tty*,int,void*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  sid; } ;

/* Variables and functions */
#define  FIONREAD_ 135 
 int /*<<< orphan*/  STRACE (char*,int /*<<< orphan*/ ) ; 
#define  TCFLSH_ 134 
#define  TCIFLUSH_ 133 
#define  TCIOFLUSH_ 132 
#define  TCOFLUSH_ 131 
#define  TIOCGPRGP_ 130 
#define  TIOCSCTTY_ 129 
#define  TIOCSPGRP_ 128 
 int _EINVAL ; 
 int _EIO ; 
 int _ENOTTY ; 
 TYPE_4__* current ; 
 int /*<<< orphan*/  lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  notify (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pids_lock ; 
 int stub1 (struct tty*,int,void*) ; 
 int tiocsctty (struct tty*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_is_current (struct tty*) ; 
 int tty_mode_ioctl (struct tty*,int,void*) ; 
 int /*<<< orphan*/  unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tty_ioctl(struct fd *fd, int cmd, void *arg) {
    int err = 0;
    struct tty *tty = fd->tty;
    lock(&tty->lock);
    if (tty->hung_up) {
        unlock(&tty->lock);
        if (cmd == TIOCSPGRP_)
            return _ENOTTY;
        return _EIO;
    }

    switch (cmd) {
        case TCFLSH_:
            // only input flushing is currently useful
            switch ((dword_t) arg) {
                case TCIFLUSH_:
                case TCIOFLUSH_:
                    tty->bufsize = 0;
                    notify(&tty->consumed);
                    break;
                case TCOFLUSH_:
                    break;
                default:
                    err = _EINVAL;
                    break;
            };
            break;

        case TIOCSCTTY_:
            err = tiocsctty(tty, (dword_t) arg);
            break;

        case TIOCGPRGP_:
            if (!tty_is_current(tty) || tty->fg_group == 0) {
                err = _ENOTTY;
                break;
            }
            STRACE("tty group = %d\n", tty->fg_group);
            *(dword_t *) arg = tty->fg_group; break;
        case TIOCSPGRP_:
            // see "aaaaaaaa" comment above
            unlock(&tty->lock);
            lock(&pids_lock);
            lock(&tty->lock);
            pid_t_ sid = current->group->sid;
            unlock(&pids_lock);
            if (!tty_is_current(tty) || sid != tty->session) {
                err = _ENOTTY;
                break;
            }
            // TODO group must be in the right session
            tty->fg_group = *(dword_t *) arg;
            STRACE("tty group set to = %d\n", tty->fg_group);
            break;

        case FIONREAD_:
            *(dword_t *) arg = tty->bufsize;
            break;

        default:
            err = tty_mode_ioctl(tty, cmd, arg);
            if (err == _ENOTTY && tty->driver->ops->ioctl)
                err = tty->driver->ops->ioctl(tty, cmd, arg);
    }

    unlock(&tty->lock);
    return err;
}