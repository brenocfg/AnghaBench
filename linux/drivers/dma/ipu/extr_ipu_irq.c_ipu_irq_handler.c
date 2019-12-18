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
typedef  unsigned long u32 ;
struct irq_desc {int dummy; } ;
struct ipu_irq_map {unsigned int irq; } ;
struct ipu_irq_bank {int /*<<< orphan*/  control; int /*<<< orphan*/  status; } ;
struct ipu {int dummy; } ;

/* Variables and functions */
 int IPU_IRQ_NR_BANKS ; 
 int /*<<< orphan*/  bank_lock ; 
 int ffs (unsigned long) ; 
 int /*<<< orphan*/  generic_handle_irq (unsigned int) ; 
 unsigned long ipu_read_reg (struct ipu*,int /*<<< orphan*/ ) ; 
 struct ipu_irq_bank* irq_bank ; 
 struct ipu* irq_desc_get_handler_data (struct irq_desc*) ; 
 int /*<<< orphan*/  pr_err (char*,int,int) ; 
 int /*<<< orphan*/  raw_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 
 struct ipu_irq_map* src2map (int) ; 

__attribute__((used)) static void ipu_irq_handler(struct irq_desc *desc)
{
	struct ipu *ipu = irq_desc_get_handler_data(desc);
	u32 status;
	int i, line;

	for (i = 0; i < IPU_IRQ_NR_BANKS; i++) {
		struct ipu_irq_bank *bank = irq_bank + i;

		raw_spin_lock(&bank_lock);
		status = ipu_read_reg(ipu, bank->status);
		/*
		 * Don't think we have to clear all interrupts here, they will
		 * be acked by ->handle_irq() (handle_level_irq). However, we
		 * might want to clear unhandled interrupts after the loop...
		 */
		status &= ipu_read_reg(ipu, bank->control);
		raw_spin_unlock(&bank_lock);
		while ((line = ffs(status))) {
			struct ipu_irq_map *map;
			unsigned int irq;

			line--;
			status &= ~(1UL << line);

			raw_spin_lock(&bank_lock);
			map = src2map(32 * i + line);
			if (!map) {
				raw_spin_unlock(&bank_lock);
				pr_err("IPU: Interrupt on unmapped source %u bank %d\n",
				       line, i);
				continue;
			}
			irq = map->irq;
			raw_spin_unlock(&bank_lock);
			generic_handle_irq(irq);
		}
	}
}