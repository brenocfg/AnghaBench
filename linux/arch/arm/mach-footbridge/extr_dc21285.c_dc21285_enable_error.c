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
struct timer_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_PCI_PERR ; 
 int /*<<< orphan*/  IRQ_PCI_SERR ; 
 int /*<<< orphan*/  del_timer (struct timer_list*) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 struct timer_list perr_timer ; 
 struct timer_list serr_timer ; 

__attribute__((used)) static void dc21285_enable_error(struct timer_list *timer)
{
	del_timer(timer);

	if (timer == &serr_timer)
		enable_irq(IRQ_PCI_SERR);
	else if (timer == &perr_timer)
		enable_irq(IRQ_PCI_PERR);
}