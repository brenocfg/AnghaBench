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
struct tty_port {int dummy; } ;
struct chan {int /*<<< orphan*/  fd; TYPE_1__* ops; scalar_t__ primary; } ;
struct TYPE_2__ {scalar_t__ winch; } ;

/* Variables and functions */
 int /*<<< orphan*/  register_winch (int /*<<< orphan*/ ,struct tty_port*) ; 

void chan_enable_winch(struct chan *chan, struct tty_port *port)
{
	if (chan && chan->primary && chan->ops->winch)
		register_winch(chan->fd, port);
}