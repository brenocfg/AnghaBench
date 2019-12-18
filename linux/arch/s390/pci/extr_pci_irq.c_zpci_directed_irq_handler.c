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
struct airq_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQIO_PCD ; 
 int /*<<< orphan*/  IRQIO_PCF ; 
 int /*<<< orphan*/  inc_irq_stat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zpci_handle_cpu_local_irq (int) ; 
 int /*<<< orphan*/  zpci_handle_fallback_irq () ; 

__attribute__((used)) static void zpci_directed_irq_handler(struct airq_struct *airq, bool floating)
{
	if (floating) {
		inc_irq_stat(IRQIO_PCF);
		zpci_handle_fallback_irq();
	} else {
		inc_irq_stat(IRQIO_PCD);
		zpci_handle_cpu_local_irq(true);
	}
}