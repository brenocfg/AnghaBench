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
struct uart_devinfo {scalar_t__ sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  UART_UNGRAB (scalar_t__) ; 

void
uart_ungrab(struct uart_devinfo *di)
{

	if (di->sc)
		UART_UNGRAB(di->sc);
}