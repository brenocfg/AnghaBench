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
struct line {int /*<<< orphan*/  port; int /*<<< orphan*/  lock; int /*<<< orphan*/  buffer; int /*<<< orphan*/  tail; int /*<<< orphan*/  head; } ;
struct chan {struct line* line; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int flush_buffer (struct line*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_port_tty_wakeup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t line_write_interrupt(int irq, void *data)
{
	struct chan *chan = data;
	struct line *line = chan->line;
	int err;

	/*
	 * Interrupts are disabled here because genirq keep irqs disabled when
	 * calling the action handler.
	 */

	spin_lock(&line->lock);
	err = flush_buffer(line);
	if (err == 0) {
		spin_unlock(&line->lock);
		return IRQ_NONE;
	} else if ((err < 0) && (err != -EAGAIN)) {
		line->head = line->buffer;
		line->tail = line->buffer;
	}
	spin_unlock(&line->lock);

	tty_port_tty_wakeup(&line->port);

	return IRQ_HANDLED;
}