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
struct umcs7840_softc {int dummy; } ;
struct ucom_softc {int sc_portno; struct umcs7840_softc* sc_parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int,int,int) ; 
 int MCS7840_UART_MSR_NEGCTS ; 
 int MCS7840_UART_MSR_NEGDCD ; 
 int MCS7840_UART_MSR_NEGDSR ; 
 int MCS7840_UART_MSR_NEGRI ; 
 int /*<<< orphan*/  MCS7840_UART_REG_LSR ; 
 int /*<<< orphan*/  MCS7840_UART_REG_MSR ; 
 int SER_CTS ; 
 int SER_DCD ; 
 int SER_DSR ; 
 int SER_RI ; 
 int /*<<< orphan*/  umcs7840_get_UART_reg_sync (struct umcs7840_softc*,int,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void
umcs7840_cfg_get_status(struct ucom_softc *ucom, uint8_t *lsr, uint8_t *msr)
{
	struct umcs7840_softc *sc = ucom->sc_parent;
	uint8_t pn = ucom->sc_portno;
	uint8_t	hw_msr = 0;	/* local modem status register */

	/*
	 * Read status registers.  MSR bits need translation from ns16550 to
	 * SER_* values.  LSR bits are ns16550 in hardware and ucom.
	 */
	umcs7840_get_UART_reg_sync(sc, pn, MCS7840_UART_REG_LSR, lsr);
	umcs7840_get_UART_reg_sync(sc, pn, MCS7840_UART_REG_MSR, &hw_msr);

	if (hw_msr & MCS7840_UART_MSR_NEGCTS)
		*msr |= SER_CTS;

	if (hw_msr & MCS7840_UART_MSR_NEGDCD)
		*msr |= SER_DCD;

	if (hw_msr & MCS7840_UART_MSR_NEGRI)
		*msr |= SER_RI;

	if (hw_msr & MCS7840_UART_MSR_NEGDSR)
		*msr |= SER_DSR;

	DPRINTF("Port %d status: LSR=%02x MSR=%02x\n", ucom->sc_portno, *lsr, *msr);
}