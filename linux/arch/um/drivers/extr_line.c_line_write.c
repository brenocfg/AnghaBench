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
struct tty_struct {struct line* driver_data; } ;
struct line {scalar_t__ head; scalar_t__ tail; int /*<<< orphan*/  lock; TYPE_1__* driver; int /*<<< orphan*/  chan_out; } ;
struct TYPE_2__ {int /*<<< orphan*/  write_irq; } ;

/* Variables and functions */
 int buffer_data (struct line*,unsigned char const*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int write_chan (int /*<<< orphan*/ ,unsigned char const*,int,int /*<<< orphan*/ ) ; 

int line_write(struct tty_struct *tty, const unsigned char *buf, int len)
{
	struct line *line = tty->driver_data;
	unsigned long flags;
	int n, ret = 0;

	spin_lock_irqsave(&line->lock, flags);
	if (line->head != line->tail)
		ret = buffer_data(line, buf, len);
	else {
		n = write_chan(line->chan_out, buf, len,
			       line->driver->write_irq);
		if (n < 0) {
			ret = n;
			goto out_up;
		}

		len -= n;
		ret += n;
		if (len > 0)
			ret += buffer_data(line, buf + n, len);
	}
out_up:
	spin_unlock_irqrestore(&line->lock, flags);
	return ret;
}