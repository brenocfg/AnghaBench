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
struct uml_pt_regs {int dummy; } ;
struct siginfo {int dummy; } ;
struct irq_fd {scalar_t__ purge; int /*<<< orphan*/  events; } ;
struct irq_entry {struct irq_fd** irq_array; } ;

/* Variables and functions */
 int EINTR ; 
 int MAX_IRQ_TYPE ; 
 int /*<<< orphan*/  free_irqs () ; 
 int /*<<< orphan*/  irq_io_loop (struct irq_fd*,struct uml_pt_regs*) ; 
 int /*<<< orphan*/  kfree (struct irq_fd*) ; 
 scalar_t__ os_epoll_get_data_pointer (int) ; 
 scalar_t__ os_epoll_triggered (int,int /*<<< orphan*/ ) ; 
 int os_waiting_for_events_epoll () ; 

void sigio_handler(int sig, struct siginfo *unused_si, struct uml_pt_regs *regs)
{
	struct irq_entry *irq_entry;
	struct irq_fd *irq;

	int n, i, j;

	while (1) {
		/* This is now lockless - epoll keeps back-referencesto the irqs
		 * which have trigger it so there is no need to walk the irq
		 * list and lock it every time. We avoid locking by turning off
		 * IO for a specific fd by executing os_del_epoll_fd(fd) before
		 * we do any changes to the actual data structures
		 */
		n = os_waiting_for_events_epoll();

		if (n <= 0) {
			if (n == -EINTR)
				continue;
			else
				break;
		}

		for (i = 0; i < n ; i++) {
			/* Epoll back reference is the entry with 3 irq_fd
			 * leaves - one for each irq type.
			 */
			irq_entry = (struct irq_entry *)
				os_epoll_get_data_pointer(i);
			for (j = 0; j < MAX_IRQ_TYPE ; j++) {
				irq = irq_entry->irq_array[j];
				if (irq == NULL)
					continue;
				if (os_epoll_triggered(i, irq->events) > 0)
					irq_io_loop(irq, regs);
				if (irq->purge) {
					irq_entry->irq_array[j] = NULL;
					kfree(irq);
				}
			}
		}
	}

	free_irqs();
}