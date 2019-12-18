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
struct mtx {int dummy; } ;

/* Variables and functions */
 int GETREG (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INT_STATUS_ACK ; 
 int /*<<< orphan*/  SETREG (struct uart_bas*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UART_DR ; 
 int /*<<< orphan*/  UART_INT_STATUS ; 
 int /*<<< orphan*/  uart_lock (struct mtx*) ; 
 int /*<<< orphan*/  uart_unlock (struct mtx*) ; 

__attribute__((used)) static int
lowrisc_uart_getc(struct uart_bas *bas, struct mtx *hwmtx)
{
	uint32_t reg;

	uart_lock(hwmtx);
	SETREG(bas, UART_INT_STATUS, INT_STATUS_ACK);
	reg = GETREG(bas, UART_DR);
	uart_unlock(hwmtx);

	return (reg & 0xff);
}