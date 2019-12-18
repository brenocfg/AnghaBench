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
struct ti_pruss_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PRUSS_INTC_GER ; 
 int /*<<< orphan*/  PRUSS_INTC_HIER ; 
 int /*<<< orphan*/  PRUSS_INTC_SECR0 ; 
 int /*<<< orphan*/  PRUSS_INTC_SECR1 ; 
 int /*<<< orphan*/  ti_pruss_reg_write (struct ti_pruss_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static __inline void
ti_pruss_interrupts_clear(struct ti_pruss_softc *sc)
{
	/* disable global interrupt */
	ti_pruss_reg_write(sc, PRUSS_INTC_GER, 0 );

	/* clear all events */
	ti_pruss_reg_write(sc, PRUSS_INTC_SECR0, 0xFFFFFFFF);
	ti_pruss_reg_write(sc, PRUSS_INTC_SECR1, 0xFFFFFFFF);

	/* disable all host interrupts */
	ti_pruss_reg_write(sc, PRUSS_INTC_HIER, 0);
}