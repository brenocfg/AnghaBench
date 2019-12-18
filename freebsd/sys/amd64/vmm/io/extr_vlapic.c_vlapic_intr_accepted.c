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
typedef  int uint32_t ;
struct TYPE_2__ {void (* intr_accepted ) (struct vlapic*,int) ;} ;
struct vlapic {int isrvec_stk_top; int* isrvec_stk; TYPE_1__ ops; struct LAPIC* apic_page; } ;
struct LAPIC {int irr0; int isr0; } ;

/* Variables and functions */
 int ISRVEC_STK_SIZE ; 
 int /*<<< orphan*/  VLAPIC_CTR_IRR (struct vlapic*,char*) ; 
 int /*<<< orphan*/  VLAPIC_CTR_ISR (struct vlapic*,char*) ; 
 int /*<<< orphan*/  atomic_clear_int (int*,int) ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 void stub1 (struct vlapic*,int) ; 
 int /*<<< orphan*/  vlapic_update_ppr (struct vlapic*) ; 

void
vlapic_intr_accepted(struct vlapic *vlapic, int vector)
{
	struct LAPIC	*lapic = vlapic->apic_page;
	uint32_t	*irrptr, *isrptr;
	int		idx, stk_top;

	if (vlapic->ops.intr_accepted)
		return ((*vlapic->ops.intr_accepted)(vlapic, vector));

	/*
	 * clear the ready bit for vector being accepted in irr 
	 * and set the vector as in service in isr.
	 */
	idx = (vector / 32) * 4;

	irrptr = &lapic->irr0;
	atomic_clear_int(&irrptr[idx], 1 << (vector % 32));
	VLAPIC_CTR_IRR(vlapic, "vlapic_intr_accepted");

	isrptr = &lapic->isr0;
	isrptr[idx] |= 1 << (vector % 32);
	VLAPIC_CTR_ISR(vlapic, "vlapic_intr_accepted");

	/*
	 * Update the PPR
	 */
	vlapic->isrvec_stk_top++;

	stk_top = vlapic->isrvec_stk_top;
	if (stk_top >= ISRVEC_STK_SIZE)
		panic("isrvec_stk_top overflow %d", stk_top);

	vlapic->isrvec_stk[stk_top] = vector;
	vlapic_update_ppr(vlapic);
}