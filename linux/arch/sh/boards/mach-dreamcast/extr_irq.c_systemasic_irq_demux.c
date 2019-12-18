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
typedef  int __u32 ;

/* Variables and functions */
 int EMR_BASE ; 
 int ESR_BASE ; 
 int HW_EVENT_IRQ_BASE ; 
 int inl (int) ; 

int systemasic_irq_demux(int irq)
{
	__u32 emr, esr, status, level;
	__u32 j, bit;

	switch (irq) {
	case 13:
		level = 0;
		break;
	case 11:
		level = 1;
		break;
	case  9:
		level = 2;
		break;
	default:
		return irq;
	}
	emr = EMR_BASE + (level << 4) + (level << 2);
	esr = ESR_BASE + (level << 2);

	/* Mask the ESR to filter any spurious, unwanted interrupts */
	status = inl(esr);
	status &= inl(emr);

	/* Now scan and find the first set bit as the event to map */
	for (bit = 1, j = 0; j < 32; bit <<= 1, j++) {
		if (status & bit) {
			irq = HW_EVENT_IRQ_BASE + j + (level << 5);
			return irq;
		}
	}

	/* Not reached */
	return irq;
}