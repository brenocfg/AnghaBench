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
struct termios {int /*<<< orphan*/  c_cflag; scalar_t__ c_ospeed; scalar_t__ c_ispeed; } ;
struct tty {struct termios t_termios_init_out; struct termios t_termios_init_in; } ;
typedef  scalar_t__ speed_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCAL ; 

void
tty_init_console(struct tty *tp, speed_t s)
{
	struct termios *ti = &tp->t_termios_init_in;
	struct termios *to = &tp->t_termios_init_out;

	if (s != 0) {
		ti->c_ispeed = ti->c_ospeed = s;
		to->c_ispeed = to->c_ospeed = s;
	}

	ti->c_cflag |= CLOCAL;
	to->c_cflag |= CLOCAL;
}