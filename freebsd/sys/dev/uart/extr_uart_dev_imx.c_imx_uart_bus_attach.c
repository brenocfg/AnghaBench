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
struct uart_bas {int dummy; } ;
struct uart_softc {struct uart_devinfo* sc_sysdev; struct uart_bas sc_bas; } ;
struct uart_devinfo {int baudrate; int databits; int stopbits; int /*<<< orphan*/  parity; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACIEN ; 
 int /*<<< orphan*/  ADEN ; 
 int /*<<< orphan*/  AIRINTEN ; 
 int /*<<< orphan*/  ATEN ; 
 int /*<<< orphan*/  AWAKEN ; 
 int /*<<< orphan*/  BKEN ; 
 int /*<<< orphan*/  DCD ; 
 int /*<<< orphan*/  DIS (struct uart_bas*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DREN ; 
 int /*<<< orphan*/  DTRDEN ; 
 int /*<<< orphan*/  DTREN ; 
 int /*<<< orphan*/  ENA (struct uart_bas*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENIRI ; 
 int /*<<< orphan*/  ESCI ; 
 int /*<<< orphan*/  FRAERREN ; 
 int /*<<< orphan*/  IDEN ; 
 int /*<<< orphan*/  IRTS ; 
 int /*<<< orphan*/  OREN ; 
 int /*<<< orphan*/  PARERREN ; 
 int /*<<< orphan*/  REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RI ; 
 int /*<<< orphan*/  RRDYEN ; 
 int /*<<< orphan*/  RTSDEN ; 
 int /*<<< orphan*/  RTSEN ; 
 int /*<<< orphan*/  RXDMUXSEL ; 
 int /*<<< orphan*/  RXDSEN ; 
 int /*<<< orphan*/  SETREG (struct uart_bas*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TCEN ; 
 int /*<<< orphan*/  TRDYEN ; 
 int /*<<< orphan*/  TXMPTYEN ; 
 int /*<<< orphan*/  UCR1 ; 
 int /*<<< orphan*/  UCR2 ; 
 int /*<<< orphan*/  UCR3 ; 
 int /*<<< orphan*/  UCR4 ; 
 int /*<<< orphan*/  USR1 ; 
 int /*<<< orphan*/  USR2 ; 
 int /*<<< orphan*/  WKEN ; 
 int /*<<< orphan*/  imx_uart_bus_getsig (struct uart_softc*) ; 
 int /*<<< orphan*/  imx_uart_init (struct uart_bas*,int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
imx_uart_bus_attach(struct uart_softc *sc)
{
	struct uart_bas *bas;
	struct uart_devinfo *di;

	bas = &sc->sc_bas;
	if (sc->sc_sysdev != NULL) {
		di = sc->sc_sysdev;
		imx_uart_init(bas, di->baudrate, di->databits, di->stopbits,
		    di->parity);
	} else {
		imx_uart_init(bas, 115200, 8, 1, 0);
	}

	(void)imx_uart_bus_getsig(sc);

	/* Clear all pending interrupts. */
	SETREG(bas, REG(USR1), 0xffff);
	SETREG(bas, REG(USR2), 0xffff);

	DIS(bas, UCR4, DREN);
	ENA(bas, UCR1, RRDYEN);
	DIS(bas, UCR1, IDEN);
	DIS(bas, UCR3, RXDSEN);
	ENA(bas, UCR2, ATEN);
	DIS(bas, UCR1, TXMPTYEN);
	DIS(bas, UCR1, TRDYEN);
	DIS(bas, UCR4, TCEN);
	DIS(bas, UCR4, OREN);
	ENA(bas, UCR4, BKEN);
	DIS(bas, UCR4, WKEN);
	DIS(bas, UCR1, ADEN);
	DIS(bas, UCR3, ACIEN);
	DIS(bas, UCR2, ESCI);
	DIS(bas, UCR4, ENIRI);
	DIS(bas, UCR3, AIRINTEN);
	DIS(bas, UCR3, AWAKEN);
	DIS(bas, UCR3, FRAERREN);
	DIS(bas, UCR3, PARERREN);
	DIS(bas, UCR1, RTSDEN);
	DIS(bas, UCR2, RTSEN);
	DIS(bas, UCR3, DTREN);
	DIS(bas, UCR3, RI);
	DIS(bas, UCR3, DCD);
	DIS(bas, UCR3, DTRDEN);
	ENA(bas, UCR2, IRTS);
	ENA(bas, UCR3, RXDMUXSEL);

	return (0);
}