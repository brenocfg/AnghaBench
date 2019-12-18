#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  size_t uint16_t ;
struct umcs7840_softc {int sc_driver_done; TYPE_3__* sc_ports; } ;
struct ucom_softc {size_t sc_portno; TYPE_2__* sc_tty; struct umcs7840_softc* sc_parent; } ;
struct TYPE_8__ {int /*<<< orphan*/  reg_control; int /*<<< orphan*/  reg_sp; } ;
struct TYPE_7__ {int sc_lcr; int sc_mcr; } ;
struct TYPE_5__ {int c_cflag; } ;
struct TYPE_6__ {TYPE_1__ t_termios; } ;

/* Variables and functions */
 int CNO_RTSDTR ; 
 int /*<<< orphan*/  DPRINTF (char*,size_t) ; 
 int MCS7840_DEV_CONTROL1_DRIVER_DONE ; 
 int MCS7840_DEV_CONTROLx_RX_DISABLE ; 
 int /*<<< orphan*/  MCS7840_DEV_REG_CONTROL1 ; 
 int MCS7840_DEV_SPx_RESET_IN_FIFO ; 
 int MCS7840_DEV_SPx_RESET_OUT_FIFO ; 
 int MCS7840_DEV_SPx_UART_RESET ; 
 int MCS7840_UART_FCR_ENABLE ; 
 int MCS7840_UART_FCR_FLUSHRHR ; 
 int MCS7840_UART_FCR_FLUSHTHR ; 
 int MCS7840_UART_FCR_RTL_1_14 ; 
 int MCS7840_UART_IER_MODEM ; 
 int MCS7840_UART_IER_RXSTAT ; 
 int MCS7840_UART_LCR_DATALEN8 ; 
 int MCS7840_UART_LCR_STOPB1 ; 
 int MCS7840_UART_MCR_DTR ; 
 int MCS7840_UART_MCR_IE ; 
 int MCS7840_UART_MCR_RTS ; 
 int /*<<< orphan*/  MCS7840_UART_REG_FCR ; 
 int /*<<< orphan*/  MCS7840_UART_REG_IER ; 
 int /*<<< orphan*/  MCS7840_UART_REG_LCR ; 
 int /*<<< orphan*/  MCS7840_UART_REG_MCR ; 
 int /*<<< orphan*/  MCS7840_UART_REG_SCRATCHPAD ; 
 int MCS7840_UART_SCRATCHPAD_RS232 ; 
 scalar_t__ umcs7840_get_UART_reg_sync (struct umcs7840_softc*,size_t,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ umcs7840_get_reg_sync (struct umcs7840_softc*,int /*<<< orphan*/ ,int*) ; 
 TYPE_4__* umcs7840_port_registers ; 
 scalar_t__ umcs7840_set_UART_reg_sync (struct umcs7840_softc*,size_t,int /*<<< orphan*/ ,int) ; 
 scalar_t__ umcs7840_set_baudrate (struct umcs7840_softc*,size_t,int) ; 
 scalar_t__ umcs7840_set_reg_sync (struct umcs7840_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
umcs7840_cfg_open(struct ucom_softc *ucom)
{
	struct umcs7840_softc *sc = ucom->sc_parent;
	uint16_t pn = ucom->sc_portno;
	uint8_t data;

	/* If it very first open, finish global configuration */
	if (!sc->sc_driver_done) {
		/*
		 * USB enumeration is finished, pass internal memory to FIFOs
		 * If it is done in the end of "attach", kernel panics.
		 */
		if (umcs7840_get_reg_sync(sc, MCS7840_DEV_REG_CONTROL1, &data))
			return;
		data |= MCS7840_DEV_CONTROL1_DRIVER_DONE;
		if (umcs7840_set_reg_sync(sc, MCS7840_DEV_REG_CONTROL1, data))
			return;
		sc->sc_driver_done = 1;
	}
	/* Toggle reset bit on-off */
	if (umcs7840_get_reg_sync(sc, umcs7840_port_registers[pn].reg_sp, &data))
		return;
	data |= MCS7840_DEV_SPx_UART_RESET;
	if (umcs7840_set_reg_sync(sc, umcs7840_port_registers[pn].reg_sp, data))
		return;
	data &= ~MCS7840_DEV_SPx_UART_RESET;
	if (umcs7840_set_reg_sync(sc, umcs7840_port_registers[pn].reg_sp, data))
		return;

	/* Set RS-232 mode */
	if (umcs7840_set_UART_reg_sync(sc, pn, MCS7840_UART_REG_SCRATCHPAD, MCS7840_UART_SCRATCHPAD_RS232))
		return;

	/* Disable RX on time of initialization */
	if (umcs7840_get_reg_sync(sc, umcs7840_port_registers[pn].reg_control, &data))
		return;
	data |= MCS7840_DEV_CONTROLx_RX_DISABLE;
	if (umcs7840_set_reg_sync(sc, umcs7840_port_registers[pn].reg_control, data))
		return;

	/* Disable all interrupts */
	if (umcs7840_set_UART_reg_sync(sc, pn, MCS7840_UART_REG_IER, 0))
		return;

	/* Reset FIFO -- documented */
	if (umcs7840_set_UART_reg_sync(sc, pn, MCS7840_UART_REG_FCR, 0))
		return;
	if (umcs7840_set_UART_reg_sync(sc, pn, MCS7840_UART_REG_FCR,
	    MCS7840_UART_FCR_ENABLE | MCS7840_UART_FCR_FLUSHRHR |
	    MCS7840_UART_FCR_FLUSHTHR | MCS7840_UART_FCR_RTL_1_14))
		return;

	/* Set 8 bit, no parity, 1 stop bit -- documented */
	sc->sc_ports[pn].sc_lcr = MCS7840_UART_LCR_DATALEN8 | MCS7840_UART_LCR_STOPB1;
	if (umcs7840_set_UART_reg_sync(sc, pn, MCS7840_UART_REG_LCR, sc->sc_ports[pn].sc_lcr))
		return;

	/*
	 * Enable DTR/RTS on modem control, enable modem interrupts --
	 * documented
	 */
	sc->sc_ports[pn].sc_mcr = MCS7840_UART_MCR_IE;
	if (ucom->sc_tty == NULL || (ucom->sc_tty->t_termios.c_cflag & CNO_RTSDTR) == 0)
		sc->sc_ports[pn].sc_mcr |= MCS7840_UART_MCR_DTR | MCS7840_UART_MCR_RTS;
	if (umcs7840_set_UART_reg_sync(sc, pn, MCS7840_UART_REG_MCR, sc->sc_ports[pn].sc_mcr))
		return;

	/* Clearing Bulkin and Bulkout FIFO */
	if (umcs7840_get_reg_sync(sc, umcs7840_port_registers[pn].reg_sp, &data))
		return;
	data |= MCS7840_DEV_SPx_RESET_OUT_FIFO | MCS7840_DEV_SPx_RESET_IN_FIFO;
	if (umcs7840_set_reg_sync(sc, umcs7840_port_registers[pn].reg_sp, data))
		return;
	data &= ~(MCS7840_DEV_SPx_RESET_OUT_FIFO | MCS7840_DEV_SPx_RESET_IN_FIFO);
	if (umcs7840_set_reg_sync(sc, umcs7840_port_registers[pn].reg_sp, data))
		return;

	/* Set speed 9600 */
	if (umcs7840_set_baudrate(sc, pn, 9600))
		return;


	/* Finally enable all interrupts -- documented */
	/*
	 * Copied from vendor driver, I don't know why we should read LCR
	 * here
	 */
	if (umcs7840_get_UART_reg_sync(sc, pn, MCS7840_UART_REG_LCR, &sc->sc_ports[pn].sc_lcr))
		return;
	if (umcs7840_set_UART_reg_sync(sc, pn, MCS7840_UART_REG_IER,
	    MCS7840_UART_IER_RXSTAT | MCS7840_UART_IER_MODEM))
		return;

	/* Enable RX */
	if (umcs7840_get_reg_sync(sc, umcs7840_port_registers[pn].reg_control, &data))
		return;
	data &= ~MCS7840_DEV_CONTROLx_RX_DISABLE;
	if (umcs7840_set_reg_sync(sc, umcs7840_port_registers[pn].reg_control, data))
		return;

	DPRINTF("Port %d has been opened\n", pn);
}