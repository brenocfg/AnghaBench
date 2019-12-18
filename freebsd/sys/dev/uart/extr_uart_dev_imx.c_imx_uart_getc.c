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
 int /*<<< orphan*/  BRK ; 
 int FLD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int GETREG (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS (struct uart_bas*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RDR ; 
 int /*<<< orphan*/  REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  URXD ; 
 int /*<<< orphan*/  USR2 ; 
 scalar_t__ kdb_break () ; 
 int /*<<< orphan*/  uart_lock (struct mtx*) ; 
 int /*<<< orphan*/  uart_unlock (struct mtx*) ; 

__attribute__((used)) static int
imx_uart_getc(struct uart_bas *bas, struct mtx *hwmtx)
{
	int c;

	uart_lock(hwmtx);
	while (!(IS(bas, USR2, RDR)))
		;

	c = GETREG(bas, REG(URXD));
	uart_unlock(hwmtx);
#if defined(KDB)
	if (c & FLD(URXD, BRK)) {
		if (kdb_break())
			return (0);
	}
#endif
	return (c & 0xff);
}