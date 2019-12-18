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
typedef  int uint32_t ;
struct vmctx {int dummy; } ;
struct lpc_uart_softc {int iobase; int /*<<< orphan*/  uart_softc; } ;

/* Variables and functions */
 int uart_read (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uart_write (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
lpc_uart_io_handler(struct vmctx *ctx, int vcpu, int in, int port, int bytes,
		    uint32_t *eax, void *arg)
{
	int offset;
	struct lpc_uart_softc *sc = arg;

	offset = port - sc->iobase;

	switch (bytes) {
	case 1:
		if (in)
			*eax = uart_read(sc->uart_softc, offset);
		else
			uart_write(sc->uart_softc, offset, *eax);
		break;
	case 2:
		if (in) {
			*eax = uart_read(sc->uart_softc, offset);
			*eax |= uart_read(sc->uart_softc, offset + 1) << 8;
		} else {
			uart_write(sc->uart_softc, offset, *eax);
			uart_write(sc->uart_softc, offset + 1, *eax >> 8);
		}
		break;
	default:
		return (-1);
	}

	return (0);
}