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
typedef  int /*<<< orphan*/  t_Isr ;
typedef  int /*<<< orphan*/  t_Handle ;
typedef  int t_Error ;
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int flags; int /*<<< orphan*/  cookie; int /*<<< orphan*/  arg; int /*<<< orphan*/ * handler; } ;

/* Variables and functions */
 int E_BUSY ; 
 int E_OK ; 
 unsigned int INTR_EXCL ; 
 unsigned int INTR_MPSAFE ; 
 unsigned int INTR_TYPE_NET ; 
 scalar_t__ XX_FmanNeedsIntrFix (uintptr_t) ; 
 int XX_INTR_FLAG_PREALLOCATED ; 
 TYPE_1__* XX_IntrInfo ; 
 scalar_t__ XX_IsPortalIntr (uintptr_t) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,struct resource*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int powerpc_bind_intr (uintptr_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_device (struct resource*) ; 
 uintptr_t rman_get_start (struct resource*) ; 

t_Error
XX_SetIntr(uintptr_t irq, t_Isr *f_Isr, t_Handle handle)
{
	device_t dev;
	struct resource *r;
	unsigned int flags;
	int err;

	r = (struct resource *)irq;
	dev = rman_get_device(r);
	irq = rman_get_start(r);

	/* Handle preallocated interrupts */
	if (XX_IntrInfo[irq].flags & XX_INTR_FLAG_PREALLOCATED) {
		if (XX_IntrInfo[irq].handler != NULL)
			return (E_BUSY);

		XX_IntrInfo[irq].handler = f_Isr;
		XX_IntrInfo[irq].arg = handle;

		return (E_OK);
	}

	flags = INTR_TYPE_NET | INTR_MPSAFE;

	/* BMAN/QMAN Portal interrupts must be exlusive */
	if (XX_IsPortalIntr(irq))
		flags |= INTR_EXCL;

	err = bus_setup_intr(dev, r, flags, NULL, f_Isr, handle,
		    &XX_IntrInfo[irq].cookie);
	if (err)
		goto finish;

	/*
	 * XXX: Bind FMan IRQ to CPU0. Current interrupt subsystem directs each
	 * interrupt to all CPUs. Race between an interrupt assertion and
	 * masking may occur and interrupt handler may be called multiple times
	 * per one interrupt. FMan doesn't support such a situation. Workaround
	 * is to bind FMan interrupt to one CPU0 only.
	 */
#ifdef SMP
	if (XX_FmanNeedsIntrFix(irq))
		err = powerpc_bind_intr(irq, 0);
#endif
finish:
	return (err);
}