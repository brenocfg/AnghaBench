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
struct mtx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDNC_UART_CHAN_STAT_REG ; 
 int CDNC_UART_CHAN_STAT_REG_RXEMPTY ; 
 int /*<<< orphan*/  CDNC_UART_FIFO ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int RD4 (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_lock (struct mtx*) ; 
 int /*<<< orphan*/  uart_unlock (struct mtx*) ; 

__attribute__((used)) static int
cdnc_uart_getc(struct uart_bas *bas, struct mtx *mtx)
{
	int c;

	uart_lock(mtx);

	while ((RD4(bas, CDNC_UART_CHAN_STAT_REG) &
		CDNC_UART_CHAN_STAT_REG_RXEMPTY) != 0) {
		uart_unlock(mtx);
		DELAY(4);
		uart_lock(mtx);
	}
	
	c = RD4(bas, CDNC_UART_FIFO);
	
	uart_unlock(mtx);

	c &= 0xff;
	return (c);
}