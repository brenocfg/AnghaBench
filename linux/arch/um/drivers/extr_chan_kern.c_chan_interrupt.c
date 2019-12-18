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
struct line {struct chan* chan_out; struct tty_port port; int /*<<< orphan*/  task; struct chan* chan_in; } ;
struct chan {scalar_t__ primary; int /*<<< orphan*/  data; int /*<<< orphan*/  fd; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* read ) (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  TTY_NORMAL ; 
 int /*<<< orphan*/  close_one_chan (struct chan*,int) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int) ; 
 int stub1 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_buffer_request_room (struct tty_port*,int) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (struct tty_port*) ; 
 int /*<<< orphan*/  tty_insert_flip_char (struct tty_port*,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_port_tty_hangup (struct tty_port*,int) ; 

void chan_interrupt(struct line *line, int irq)
{
	struct tty_port *port = &line->port;
	struct chan *chan = line->chan_in;
	int err;
	char c;

	if (!chan || !chan->ops->read)
		goto out;

	do {
		if (!tty_buffer_request_room(port, 1)) {
			schedule_delayed_work(&line->task, 1);
			goto out;
		}
		err = chan->ops->read(chan->fd, &c, chan->data);
		if (err > 0)
			tty_insert_flip_char(port, c, TTY_NORMAL);
	} while (err > 0);

	if (err == -EIO) {
		if (chan->primary) {
			tty_port_tty_hangup(&line->port, false);
			if (line->chan_out != chan)
				close_one_chan(line->chan_out, 1);
		}
		close_one_chan(chan, 1);
		if (chan->primary)
			return;
	}
 out:
	tty_flip_buffer_push(port);
}