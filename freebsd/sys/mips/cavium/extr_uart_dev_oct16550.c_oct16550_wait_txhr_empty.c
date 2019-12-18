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

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int LSR_THRE ; 
 int /*<<< orphan*/  REG_LSR ; 
 int /*<<< orphan*/  REG_USR ; 
 int USR_TXFIFO_NOTFULL ; 
 int uart_getreg (struct uart_bas*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void oct16550_wait_txhr_empty (struct uart_bas *bas, int limit, int delay)
{
    while (((uart_getreg(bas, REG_LSR) & LSR_THRE) == 0) &&
           ((uart_getreg(bas, REG_USR) & USR_TXFIFO_NOTFULL) == 0))
        DELAY(delay);
}