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
 unsigned int CRTSCTS ; 
 int /*<<< orphan*/  PSCR ; 
 unsigned short __raw_readw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writew (unsigned short,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sh7722_sci_init_pins(struct uart_port *port, unsigned int cflag)
{
	unsigned short data;

	if (port->mapbase == 0xffe00000) {
		data = __raw_readw(PSCR);
		data &= ~0x03cf;
		if (!(cflag & CRTSCTS))
			data |= 0x0340;

		__raw_writew(data, PSCR);
	}
}