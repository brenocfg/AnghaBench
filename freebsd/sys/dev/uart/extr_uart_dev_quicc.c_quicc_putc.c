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
typedef  int uint16_t ;
struct uart_bas {int chan; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  QUICC_PRAM_SCC_UART_TOSEQ (int) ; 
 int quicc_read2 (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quicc_write2 (struct uart_bas*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
quicc_putc(struct uart_bas *bas, int c)
{
	int unit;
	uint16_t toseq;

	unit = bas->chan - 1;
	while (quicc_read2(bas, QUICC_PRAM_SCC_UART_TOSEQ(unit)) & 0x2000)
		DELAY(10);

	toseq = 0x2000 | (c & 0xff);
	quicc_write2(bas, QUICC_PRAM_SCC_UART_TOSEQ(unit), toseq);
}