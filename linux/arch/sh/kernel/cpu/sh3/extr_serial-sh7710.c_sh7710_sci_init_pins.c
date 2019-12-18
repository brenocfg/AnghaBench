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
struct uart_port {int mapbase; } ;

/* Variables and functions */
 int /*<<< orphan*/  PACR ; 
 int /*<<< orphan*/  PBCR ; 
 int __raw_readw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writew (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sh7710_sci_init_pins(struct uart_port *port, unsigned int cflag)
{
	if (port->mapbase == 0xA4400000) {
		__raw_writew(__raw_readw(PACR) & 0xffc0, PACR);
		__raw_writew(__raw_readw(PBCR) & 0x0fff, PBCR);
	} else if (port->mapbase == 0xA4410000)
		__raw_writew(__raw_readw(PBCR) & 0xf003, PBCR);
}