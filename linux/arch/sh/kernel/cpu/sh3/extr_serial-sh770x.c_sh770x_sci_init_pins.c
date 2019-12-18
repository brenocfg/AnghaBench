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
struct uart_port {int dummy; } ;

/* Variables and functions */
 unsigned int CRTSCTS ; 
 int /*<<< orphan*/  SCPCR ; 
 int /*<<< orphan*/  SCPDR ; 
 unsigned short __raw_readb (int /*<<< orphan*/ ) ; 
 unsigned short __raw_readw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writeb (unsigned short,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writew (unsigned short,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sh770x_sci_init_pins(struct uart_port *port, unsigned int cflag)
{
	unsigned short data;

	/* We need to set SCPCR to enable RTS/CTS */
	data = __raw_readw(SCPCR);
	/* Clear out SCP7MD1,0, SCP6MD1,0, SCP4MD1,0*/
	__raw_writew(data & 0x0fcf, SCPCR);

	if (!(cflag & CRTSCTS)) {
		/* We need to set SCPCR to enable RTS/CTS */
		data = __raw_readw(SCPCR);
		/* Clear out SCP7MD1,0, SCP4MD1,0,
		   Set SCP6MD1,0 = {01} (output)  */
		__raw_writew((data & 0x0fcf) | 0x1000, SCPCR);

		data = __raw_readb(SCPDR);
		/* Set /RTS2 (bit6) = 0 */
		__raw_writeb(data & 0xbf, SCPDR);
	}
}