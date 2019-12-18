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
struct si_sm_io {scalar_t__ irq; int /*<<< orphan*/  dev; int /*<<< orphan*/  irq_cleanup; int /*<<< orphan*/  irq_handler_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  SI_DEVICE_NAME ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ipmi_irq_finish_setup (struct si_sm_io*) ; 
 int /*<<< orphan*/  ipmi_si_irq_handler ; 
 int request_irq (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  std_irq_cleanup ; 

int ipmi_std_irq_setup(struct si_sm_io *io)
{
	int rv;

	if (!io->irq)
		return 0;

	rv = request_irq(io->irq,
			 ipmi_si_irq_handler,
			 IRQF_SHARED,
			 SI_DEVICE_NAME,
			 io->irq_handler_data);
	if (rv) {
		dev_warn(io->dev, "%s unable to claim interrupt %d,"
			 " running polled\n",
			 SI_DEVICE_NAME, io->irq);
		io->irq = 0;
	} else {
		io->irq_cleanup = std_irq_cleanup;
		ipmi_irq_finish_setup(io);
		dev_info(io->dev, "Using irq %d\n", io->irq);
	}

	return rv;
}