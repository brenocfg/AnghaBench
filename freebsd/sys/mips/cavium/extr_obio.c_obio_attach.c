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
struct TYPE_3__ {char* rm_descr; void* rm_type; } ;
struct obio_softc {int oba_size; TYPE_1__ oba_irq_rman; scalar_t__ oba_addr; TYPE_1__ oba_rman; int /*<<< orphan*/  oba_st; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ CVMX_MIO_UARTX_RBR (int /*<<< orphan*/ ) ; 
 scalar_t__ OCTEON_IRQ_UART0 ; 
 scalar_t__ OCTEON_IRQ_UART1 ; 
 void* RMAN_ARRAY ; 
 int /*<<< orphan*/  bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_probe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 struct obio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_bus_space_generic ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ rman_init (TYPE_1__*) ; 
 scalar_t__ rman_manage_region (TYPE_1__*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int
obio_attach(device_t dev)
{
	struct obio_softc *sc = device_get_softc(dev);

	sc->oba_st = mips_bus_space_generic;
	/*
	 * XXX
	 * Here and elsewhere using RBR as a base address because it kind of
	 * is, but that feels pretty sloppy.  Should consider adding a define
	 * that's more semantic, at least.
	 */
	sc->oba_addr = CVMX_MIO_UARTX_RBR(0);
	sc->oba_size = 0x10000;
	sc->oba_rman.rm_type = RMAN_ARRAY;
	sc->oba_rman.rm_descr = "OBIO I/O";
	if (rman_init(&sc->oba_rman) != 0 ||
	    rman_manage_region(&sc->oba_rman,
	    sc->oba_addr, sc->oba_addr + sc->oba_size) != 0)
		panic("obio_attach: failed to set up I/O rman");
	sc->oba_irq_rman.rm_type = RMAN_ARRAY;
	sc->oba_irq_rman.rm_descr = "OBIO IRQ";

	/* 
	 * This module is intended for UART purposes only and
	 * manages IRQs for UART0 and UART1.
	 */
	if (rman_init(&sc->oba_irq_rman) != 0 ||
	    rman_manage_region(&sc->oba_irq_rman, OCTEON_IRQ_UART0, OCTEON_IRQ_UART1) != 0)
		panic("obio_attach: failed to set up IRQ rman");

	device_add_child(dev, "uart", 1);  /* Setup Uart-1 first. */
	device_add_child(dev, "uart", 0);  /* Uart-0 next. So it is first in console list */
	bus_generic_probe(dev);
	bus_generic_attach(dev);
	return (0);
}