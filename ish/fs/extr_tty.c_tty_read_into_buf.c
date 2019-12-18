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
struct tty {size_t bufsize; int /*<<< orphan*/  consumed; scalar_t__ buf_flag; scalar_t__ buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (void*,scalar_t__,size_t) ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,size_t) ; 
 int /*<<< orphan*/  notify (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tty_read_into_buf(struct tty *tty, void *buf, size_t bufsize) {
    assert(bufsize <= tty->bufsize);
    memcpy(buf, tty->buf, bufsize);
    tty->bufsize -= bufsize;
    memmove(tty->buf, tty->buf + bufsize, tty->bufsize); // magic!
    memmove(tty->buf_flag, tty->buf_flag + bufsize, tty->bufsize);
    notify(&tty->consumed);
}