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

/* Variables and functions */
 int /*<<< orphan*/  e ; 
 int /*<<< orphan*/  re_putc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int tty_get_signal_character (int /*<<< orphan*/ ,int) ; 

void
rl_echo_signal_char(int sig)
{
	int c = tty_get_signal_character(e, sig);
	if (c == -1)
		return;
	re_putc(e, c, 0);
}