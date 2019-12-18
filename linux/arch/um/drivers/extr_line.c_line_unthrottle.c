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
struct line {TYPE_1__* driver; scalar_t__ throttled; } ;
struct TYPE_2__ {int /*<<< orphan*/  read_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  chan_interrupt (struct line*,int /*<<< orphan*/ ) ; 

void line_unthrottle(struct tty_struct *tty)
{
	struct line *line = tty->driver_data;

	line->throttled = 0;
	chan_interrupt(line, line->driver->read_irq);
}