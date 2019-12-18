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
struct uart_softc {int sc_pps_mode; int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
#define  UART_PPS_CTS 130 
#define  UART_PPS_DCD 129 
#define  UART_PPS_DISABLED 128 
 int UART_PPS_INVERT_PULSE ; 
 int UART_PPS_NARROW_PULSE ; 
 int UART_PPS_SIGNAL_MASK ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void
uart_pps_print_mode(struct uart_softc *sc)
{

	device_printf(sc->sc_dev, "PPS capture mode: ");
	switch(sc->sc_pps_mode & UART_PPS_SIGNAL_MASK) {
	case UART_PPS_DISABLED:
		printf("disabled");
		break;
	case UART_PPS_CTS:
		printf("CTS");
		break;
	case UART_PPS_DCD:
		printf("DCD");
		break;
	default:
		printf("invalid");
		break;
	}
	if (sc->sc_pps_mode & UART_PPS_INVERT_PULSE)
		printf("-Inverted");
	if (sc->sc_pps_mode & UART_PPS_NARROW_PULSE)
		printf("-NarrowPulse");
	printf("\n");
}