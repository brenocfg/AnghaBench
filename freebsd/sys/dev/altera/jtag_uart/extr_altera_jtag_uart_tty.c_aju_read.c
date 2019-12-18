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
struct altera_jtag_uart_softc {char* ajus_buffer_datap; scalar_t__* ajus_buffer_validp; } ;

/* Variables and functions */
 int /*<<< orphan*/  AJU_LOCK_ASSERT (struct altera_jtag_uart_softc*) ; 
 int /*<<< orphan*/  aju_readable (struct altera_jtag_uart_softc*) ; 

__attribute__((used)) static char
aju_read(struct altera_jtag_uart_softc *sc)
{

	AJU_LOCK_ASSERT(sc);

	while (!aju_readable(sc));
	*sc->ajus_buffer_validp = 0;
	return (*sc->ajus_buffer_datap);
}