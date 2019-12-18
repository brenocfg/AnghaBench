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
typedef  int u_char ;
struct uart_bas {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  REG_IIR ; 
 int /*<<< orphan*/  REG_MCR ; 
 int /*<<< orphan*/  REG_USR ; 
 int uart_getreg (struct uart_bas*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
oct16550_probe (struct uart_bas *bas)
{
	u_char val;

	/* Check known 0 bits that don't depend on DLAB. */
	val = uart_getreg(bas, REG_IIR);
	if (val & 0x30)
		return (ENXIO);
	val = uart_getreg(bas, REG_MCR);
	if (val & 0xc0)
		return (ENXIO);
	val = uart_getreg(bas, REG_USR);
        if (val & 0xe0)
            	return (ENXIO);
	return (0);
}