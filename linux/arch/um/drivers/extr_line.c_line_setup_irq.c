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
struct line_driver {int /*<<< orphan*/  write_irq_name; int /*<<< orphan*/  write_irq; int /*<<< orphan*/  read_irq_name; int /*<<< orphan*/  read_irq; } ;
struct line {struct line_driver* driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  IRQ_READ ; 
 int /*<<< orphan*/  IRQ_WRITE ; 
 int /*<<< orphan*/  line_interrupt ; 
 int /*<<< orphan*/  line_write_interrupt ; 
 int um_request_irq (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

int line_setup_irq(int fd, int input, int output, struct line *line, void *data)
{
	const struct line_driver *driver = line->driver;
	int err = 0;

	if (input)
		err = um_request_irq(driver->read_irq, fd, IRQ_READ,
				     line_interrupt, IRQF_SHARED,
				     driver->read_irq_name, data);
	if (err)
		return err;
	if (output)
		err = um_request_irq(driver->write_irq, fd, IRQ_WRITE,
				     line_write_interrupt, IRQF_SHARED,
				     driver->write_irq_name, data);
	return err;
}