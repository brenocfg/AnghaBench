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
struct fsa9480_usbsw {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  fsa9480_detect_dev (struct fsa9480_usbsw*) ; 
 int /*<<< orphan*/  fsa9480_read_irq (struct fsa9480_usbsw*,int*) ; 

__attribute__((used)) static irqreturn_t fsa9480_irq_handler(int irq, void *data)
{
	struct fsa9480_usbsw *usbsw = data;
	int intr = 0;

	/* clear interrupt */
	fsa9480_read_irq(usbsw, &intr);
	if (!intr)
		return IRQ_NONE;

	/* device detection */
	fsa9480_detect_dev(usbsw);

	return IRQ_HANDLED;
}