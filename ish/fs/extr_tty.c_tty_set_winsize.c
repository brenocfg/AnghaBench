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
struct winsize_ {int dummy; } ;
struct tty {scalar_t__ fg_group; struct winsize_ winsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGINFO_NIL ; 
 int /*<<< orphan*/  SIGWINCH_ ; 
 int /*<<< orphan*/  send_group_signal (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void tty_set_winsize(struct tty *tty, struct winsize_ winsize) {
    tty->winsize = winsize;
    if (tty->fg_group != 0)
        send_group_signal(tty->fg_group, SIGWINCH_, SIGINFO_NIL);
}