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
struct winsize {int dummy; } ;
struct tty {struct winsize t_winsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGWINCH ; 
 scalar_t__ memcmp (struct winsize*,struct winsize const*,int) ; 
 int /*<<< orphan*/  tty_signal_pgrp (struct tty*,int /*<<< orphan*/ ) ; 

void
tty_set_winsize(struct tty *tp, const struct winsize *wsz)
{

	if (memcmp(&tp->t_winsize, wsz, sizeof(*wsz)) == 0)
		return;
	tp->t_winsize = *wsz;
	tty_signal_pgrp(tp, SIGWINCH);
}