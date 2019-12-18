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
struct altera_jtag_uart_softc {int dummy; } ;

/* Variables and functions */
 int ALTERA_JTAG_UART_CONTROL_WSPACE ; 
 int aju_control_read (struct altera_jtag_uart_softc*) ; 

__attribute__((used)) static inline int
aju_writable(struct altera_jtag_uart_softc *sc)
{

	return ((aju_control_read(sc) &
	    ALTERA_JTAG_UART_CONTROL_WSPACE) != 0);
}