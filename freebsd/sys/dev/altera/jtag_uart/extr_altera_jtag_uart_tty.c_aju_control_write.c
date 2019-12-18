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
typedef  int /*<<< orphan*/  uint32_t ;
struct altera_jtag_uart_softc {int /*<<< orphan*/  ajus_mem_res; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALTERA_JTAG_UART_CONTROL_OFF ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htole32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
aju_control_write(struct altera_jtag_uart_softc *sc, uint32_t v)
{

	bus_write_4(sc->ajus_mem_res, ALTERA_JTAG_UART_CONTROL_OFF,
	    htole32(v));
}