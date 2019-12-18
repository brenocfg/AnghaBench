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
struct tty {int* buf_flag; int /*<<< orphan*/  bufsize; } ;

/* Variables and functions */
 int* memchr (int*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t tty_canon_size(struct tty *tty) {
    bool *flag_ptr = memchr(tty->buf_flag, true, tty->bufsize);
    if (flag_ptr == NULL)
        return -1;
    return flag_ptr - tty->buf_flag + 1;
}