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
struct uart_bas {scalar_t__ chan; } ;
struct mtx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int QUICC_PRAM_SCC_RBASE (scalar_t__) ; 
 int quicc_read2 (struct uart_bas*,int) ; 
 scalar_t__ quicc_read4 (struct uart_bas*,int) ; 
 int /*<<< orphan*/  quicc_write2 (struct uart_bas*,int,int) ; 
 int /*<<< orphan*/  uart_lock (struct mtx*) ; 
 int /*<<< orphan*/  uart_unlock (struct mtx*) ; 

__attribute__((used)) static int
quicc_getc(struct uart_bas *bas, struct mtx *hwmtx)
{
	volatile char *buf;
	int c;
	uint16_t rb, sc;

	uart_lock(hwmtx);

	rb = quicc_read2(bas, QUICC_PRAM_SCC_RBASE(bas->chan - 1));

	while ((sc = quicc_read2(bas, rb)) & 0x8000) {
		uart_unlock(hwmtx);
		DELAY(4);
		uart_lock(hwmtx);
	}

	buf = (void *)(uintptr_t)quicc_read4(bas, rb + 4);
	c = *buf;
	quicc_write2(bas, rb, sc | 0x8000);

	uart_unlock(hwmtx);

	return (c);
}