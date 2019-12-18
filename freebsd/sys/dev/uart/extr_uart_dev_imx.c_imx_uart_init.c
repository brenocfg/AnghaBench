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
struct uart_bas {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIS (struct uart_bas*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENA (struct uart_bas*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int FLD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int GETREG (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int IMXUART_UFCR_RFDIV_DIV1 ; 
 int IMXUART_UFCR_RFDIV_MASK ; 
 int IMXUART_UFCR_RXTL_MASK ; 
 int IMXUART_UFCR_RXTL_SHIFT ; 
 int IMXUART_UFCR_TXTL_MASK ; 
 int IMXUART_UFCR_TXTL_SHIFT ; 
 int IMX_FIFOSZ ; 
 int IMX_RXFIFO_LEVEL ; 
 int IMX_TXFIFO_LEVEL ; 
 int /*<<< orphan*/  PREN ; 
 int /*<<< orphan*/  PROE ; 
 int /*<<< orphan*/  REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RXEN ; 
 int /*<<< orphan*/  SET (struct uart_bas*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SETREG (struct uart_bas*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  STPB ; 
 int /*<<< orphan*/  TXEN ; 
 int /*<<< orphan*/  UARTEN ; 
#define  UART_PARITY_EVEN 132 
#define  UART_PARITY_MARK 131 
#define  UART_PARITY_NONE 130 
#define  UART_PARITY_ODD 129 
#define  UART_PARITY_SPACE 128 
 int /*<<< orphan*/  UBIR ; 
 int /*<<< orphan*/  UBMR ; 
 int /*<<< orphan*/  UCR1 ; 
 int /*<<< orphan*/  UCR2 ; 
 int /*<<< orphan*/  UFCR ; 
 int /*<<< orphan*/  WS ; 
 int imx_ccm_uart_hz () ; 

__attribute__((used)) static void
imx_uart_init(struct uart_bas *bas, int baudrate, int databits, 
    int stopbits, int parity)
{
	uint32_t baseclk, reg;

        /* Enable the device and the RX/TX channels. */
	SET(bas, REG(UCR1), FLD(UCR1, UARTEN));
	SET(bas, REG(UCR2), FLD(UCR2, RXEN) | FLD(UCR2, TXEN));

	if (databits == 7)
		DIS(bas, UCR2, WS);
	else
		ENA(bas, UCR2, WS);

	if (stopbits == 2)
		ENA(bas, UCR2, STPB);
	else
		DIS(bas, UCR2, STPB);

	switch (parity) {
	case UART_PARITY_ODD:
		DIS(bas, UCR2, PROE);
		ENA(bas, UCR2, PREN);
		break;
	case UART_PARITY_EVEN:
		ENA(bas, UCR2, PROE);
		ENA(bas, UCR2, PREN);
		break;
	case UART_PARITY_MARK:
	case UART_PARITY_SPACE:
                /* FALLTHROUGH: Hardware doesn't support mark/space. */
	case UART_PARITY_NONE:
	default:
		DIS(bas, UCR2, PREN);
		break;
	}

	/*
	 * The hardware has an extremely flexible baud clock: it allows setting
	 * both the numerator and denominator of the divider, as well as a
	 * separate pre-divider.  We simplify the problem of coming up with a
	 * workable pair of numbers by assuming a pre-divider and numerator of
	 * one because our base clock is so fast we can reach virtually any
	 * reasonable speed with a simple divisor.  The numerator value actually
	 * includes the 16x over-sampling (so a value of 16 means divide by 1);
	 * the register value is the numerator-1, so we have a hard-coded 15.
	 * Note that a quirk of the hardware requires that both UBIR and UBMR be
	 * set back to back in order for the change to take effect.
	 */
	if (baudrate > 0) {
		baseclk = imx_ccm_uart_hz();
		reg = GETREG(bas, REG(UFCR));
		reg = (reg & ~IMXUART_UFCR_RFDIV_MASK) | IMXUART_UFCR_RFDIV_DIV1;
		SETREG(bas, REG(UFCR), reg);
		SETREG(bas, REG(UBIR), 15);
		SETREG(bas, REG(UBMR), (baseclk / baudrate) - 1);
	}

	/*
	 * Program the tx lowater and rx hiwater levels at which fifo-service
	 * interrupts are signaled.  The tx value is interpetted as "when there
	 * are only this many bytes remaining" (not "this many free").
	 */
	reg = GETREG(bas, REG(UFCR));
	reg &= ~(IMXUART_UFCR_TXTL_MASK | IMXUART_UFCR_RXTL_MASK);
	reg |= (IMX_FIFOSZ - IMX_TXFIFO_LEVEL) << IMXUART_UFCR_TXTL_SHIFT;
	reg |= IMX_RXFIFO_LEVEL << IMXUART_UFCR_RXTL_SHIFT;
	SETREG(bas, REG(UFCR), reg);
}