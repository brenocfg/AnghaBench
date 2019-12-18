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
struct uart_bas {int /*<<< orphan*/  bsh; int /*<<< orphan*/  bst; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSCOM_UFSTAT ; 
 int /*<<< orphan*/  SSCOM_UTXH ; 
 int UFSTAT_TXFULL ; 
 int bus_space_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_setreg (struct uart_bas*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
exynos4210_putc(struct uart_bas *bas, int c)
{

	while ((bus_space_read_4(bas->bst, bas->bsh, SSCOM_UFSTAT) &
		UFSTAT_TXFULL) == UFSTAT_TXFULL)
		continue;

	uart_setreg(bas, SSCOM_UTXH, c);
}