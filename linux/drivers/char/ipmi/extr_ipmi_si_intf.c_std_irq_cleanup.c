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
struct si_sm_io {int /*<<< orphan*/  irq_handler_data; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipmi_irq_start_cleanup (struct si_sm_io*) ; 

__attribute__((used)) static void std_irq_cleanup(struct si_sm_io *io)
{
	ipmi_irq_start_cleanup(io);
	free_irq(io->irq, io->irq_handler_data);
}