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
struct tty {int bufsize; char* buf; int* buf_flag; int /*<<< orphan*/  lock; int /*<<< orphan*/  consumed; } ;

/* Variables and functions */
 int _EAGAIN ; 
 int _EINTR ; 
 scalar_t__ wait_for (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tty_push_char(struct tty *tty, char ch, bool flag, int blocking) {
    while (tty->bufsize >= sizeof(tty->buf)) {
        if (!blocking)
            return _EAGAIN;
        if (wait_for(&tty->consumed, &tty->lock, NULL))
            return _EINTR;
    }
    tty->buf[tty->bufsize] = ch;
    tty->buf_flag[tty->bufsize++] = flag;
    return 0;
}