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

/* Variables and functions */
 int UART_CTRL_EN ; 
 unsigned int UART_LCRH_FEN ; 
 unsigned int UART_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UART_REG_CTRL ; 
 int /*<<< orphan*/  UART_REG_ECR ; 
 int /*<<< orphan*/  UART_REG_LCRH ; 
 int /*<<< orphan*/  UART_REG_LCRL ; 
 int /*<<< orphan*/  UART_REG_LCRM ; 
 int /*<<< orphan*/  UART_WRITE (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void uart_init(void)
{
#if 0
	unsigned int t;

	/* disable uart */
	UART_WRITE(UART_REG_CTRL, 0);

	/* keep current baud rate */
	t = UART_READ(UART_REG_LCRM);
	UART_WRITE(UART_REG_LCRM, t);
	t = UART_READ(UART_REG_LCRL);
	UART_WRITE(UART_REG_LCRL, t);

	/* keep data, stop, and parity bits, but disable FIFO */
	t = UART_READ(UART_REG_LCRH);
	t &= ~(UART_LCRH_FEN);
	UART_WRITE(UART_REG_LCRH, t );

	/* clear error bits */
	UART_WRITE(UART_REG_ECR, 0xFF);

	/* enable uart, and disable interrupts */
	UART_WRITE(UART_REG_CTRL, UART_CTRL_EN);
#endif
}