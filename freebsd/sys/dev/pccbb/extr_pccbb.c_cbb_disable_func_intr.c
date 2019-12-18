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
typedef  int uint8_t ;
struct cbb_softc {int /*<<< orphan*/ * exca; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXCA_INTR ; 
 int EXCA_INTR_IRQ_MASK ; 
 int EXCA_INTR_IRQ_RESERVED1 ; 
 int exca_getb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exca_putb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void
cbb_disable_func_intr(struct cbb_softc *sc)
{
#if 0
	uint8_t reg;

	reg = (exca_getb(&sc->exca[0], EXCA_INTR) & ~EXCA_INTR_IRQ_MASK) | 
	    EXCA_INTR_IRQ_RESERVED1;
	exca_putb(&sc->exca[0], EXCA_INTR, reg);
#endif
}