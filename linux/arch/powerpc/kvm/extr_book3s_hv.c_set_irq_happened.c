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
struct TYPE_2__ {int /*<<< orphan*/  irq_happened; } ;

/* Variables and functions */
#define  BOOK3S_INTERRUPT_EXTERNAL 131 
#define  BOOK3S_INTERRUPT_HMI 130 
#define  BOOK3S_INTERRUPT_H_DOORBELL 129 
#define  BOOK3S_INTERRUPT_SYSTEM_RESET 128 
 int /*<<< orphan*/  PACA_IRQ_DBELL ; 
 int /*<<< orphan*/  PACA_IRQ_EE ; 
 int /*<<< orphan*/  PACA_IRQ_HMI ; 
 TYPE_1__* local_paca ; 
 int /*<<< orphan*/  replay_system_reset () ; 

__attribute__((used)) static void set_irq_happened(int trap)
{
	switch (trap) {
	case BOOK3S_INTERRUPT_EXTERNAL:
		local_paca->irq_happened |= PACA_IRQ_EE;
		break;
	case BOOK3S_INTERRUPT_H_DOORBELL:
		local_paca->irq_happened |= PACA_IRQ_DBELL;
		break;
	case BOOK3S_INTERRUPT_HMI:
		local_paca->irq_happened |= PACA_IRQ_HMI;
		break;
	case BOOK3S_INTERRUPT_SYSTEM_RESET:
		replay_system_reset();
		break;
	}
}