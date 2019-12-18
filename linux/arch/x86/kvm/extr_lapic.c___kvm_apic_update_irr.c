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
typedef  int u32 ;

/* Variables and functions */
 int APIC_IRR ; 
 int READ_ONCE (int) ; 
 int __fls (int) ; 
 int xchg (int*,int /*<<< orphan*/ ) ; 

bool __kvm_apic_update_irr(u32 *pir, void *regs, int *max_irr)
{
	u32 i, vec;
	u32 pir_val, irr_val, prev_irr_val;
	int max_updated_irr;

	max_updated_irr = -1;
	*max_irr = -1;

	for (i = vec = 0; i <= 7; i++, vec += 32) {
		pir_val = READ_ONCE(pir[i]);
		irr_val = *((u32 *)(regs + APIC_IRR + i * 0x10));
		if (pir_val) {
			prev_irr_val = irr_val;
			irr_val |= xchg(&pir[i], 0);
			*((u32 *)(regs + APIC_IRR + i * 0x10)) = irr_val;
			if (prev_irr_val != irr_val) {
				max_updated_irr =
					__fls(irr_val ^ prev_irr_val) + vec;
			}
		}
		if (irr_val)
			*max_irr = __fls(irr_val) + vec;
	}

	return ((max_updated_irr != -1) &&
		(max_updated_irr == *max_irr));
}