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
struct pt_regs {int dummy; } ;

/* Variables and functions */
 unsigned long ISR ; 
 int /*<<< orphan*/  do_IRQ (int,struct pt_regs*) ; 

void process_int(int vec, struct pt_regs *fp)
{
	int irq;
	int mask;

	unsigned long pend = ISR;

	while (pend) {
		if (pend & 0x0000ffff) {
			if (pend & 0x000000ff) {
				if (pend & 0x0000000f) {
					mask = 0x00000001;
					irq = 0;
				} else {
					mask = 0x00000010;
					irq = 4;
				}
			} else {
				if (pend & 0x00000f00) {
					mask = 0x00000100;
					irq = 8;
				} else {
					mask = 0x00001000;
					irq = 12;
				}
			}
		} else {
			if (pend & 0x00ff0000) {
				if (pend & 0x000f0000) {
					mask = 0x00010000;
					irq = 16;
				} else {
					mask = 0x00100000;
					irq = 20;
				}
			} else {
				if (pend & 0x0f000000) {
					mask = 0x01000000;
					irq = 24;
				} else {
					mask = 0x10000000;
					irq = 28;
				}
			}
		}

		while (! (mask & pend)) {
			mask <<=1;
			irq++;
		}

		do_IRQ(irq, fp);
		pend &= ~mask;
	}
}