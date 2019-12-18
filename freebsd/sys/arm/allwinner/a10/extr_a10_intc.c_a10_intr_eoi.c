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
typedef  int u_int ;
struct a10_aintc_softc {int /*<<< orphan*/  mtx; } ;

/* Variables and functions */
 int SW_INT_IRQNO_ENMI ; 
 int /*<<< orphan*/  SW_INT_IRQ_PENDING_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aintc_write_4 (struct a10_aintc_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __inline void
a10_intr_eoi(struct a10_aintc_softc *sc, u_int irq)
{

	if (irq != SW_INT_IRQNO_ENMI)
		return;
	mtx_lock_spin(&sc->mtx);
	aintc_write_4(sc, SW_INT_IRQ_PENDING_REG(0),
	    (1 << SW_INT_IRQNO_ENMI));
	mtx_unlock_spin(&sc->mtx);
}