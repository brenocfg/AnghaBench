#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int eax; int ecx; } ;
typedef  TYPE_1__ SMMRegisters ;

/* Variables and functions */
 unsigned char inb (int) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  outb (int,int) ; 
 int /*<<< orphan*/  outw (int,int) ; 
 int tosh_id ; 

__attribute__((used)) static int tosh_emulate_fan(SMMRegisters *regs)
{
	unsigned long eax,ecx,flags;
	unsigned char al;

	eax = regs->eax & 0xff00;
	ecx = regs->ecx & 0xffff;

	/* Portage 610CT */

	if (tosh_id==0xfccb) {
		if (eax==0xfe00) {
			/* fan status */
			local_irq_save(flags);
			outb(0xbe, 0xe4);
			al = inb(0xe5);
			local_irq_restore(flags);
			regs->eax = 0x00;
			regs->ecx = (unsigned int) (al & 0x01);
		}
		if ((eax==0xff00) && (ecx==0x0000)) {
			/* fan off */
			local_irq_save(flags);
			outb(0xbe, 0xe4);
			al = inb(0xe5);
			outb(0xbe, 0xe4);
			outb (al | 0x01, 0xe5);
			local_irq_restore(flags);
			regs->eax = 0x00;
			regs->ecx = 0x00;
		}
		if ((eax==0xff00) && (ecx==0x0001)) {
			/* fan on */
			local_irq_save(flags);
			outb(0xbe, 0xe4);
			al = inb(0xe5);
			outb(0xbe, 0xe4);
			outb(al & 0xfe, 0xe5);
			local_irq_restore(flags);
			regs->eax = 0x00;
			regs->ecx = 0x01;
		}
	}

	/* Tecra 700CS/CDT */

	if (tosh_id==0xfccc) {
		if (eax==0xfe00) {
			/* fan status */
			local_irq_save(flags);
			outb(0xe0, 0xe4);
			al = inb(0xe5);
			local_irq_restore(flags);
			regs->eax = 0x00;
			regs->ecx = al & 0x01;
		}
		if ((eax==0xff00) && (ecx==0x0000)) {
			/* fan off */
			local_irq_save(flags);
			outb(0xe0, 0xe4);
			al = inb(0xe5);
			outw(0xe0 | ((al & 0xfe) << 8), 0xe4);
			local_irq_restore(flags);
			regs->eax = 0x00;
			regs->ecx = 0x00;
		}
		if ((eax==0xff00) && (ecx==0x0001)) {
			/* fan on */
			local_irq_save(flags);
			outb(0xe0, 0xe4);
			al = inb(0xe5);
			outw(0xe0 | ((al | 0x01) << 8), 0xe4);
			local_irq_restore(flags);
			regs->eax = 0x00;
			regs->ecx = 0x01;
		}
	}

	return 0;
}