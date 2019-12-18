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
typedef  int /*<<< orphan*/  uint32_t ;
struct consdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AJU_CONSOLE_LOCK () ; 
 int /*<<< orphan*/  AJU_CONSOLE_LOCK_INIT () ; 
 int /*<<< orphan*/  AJU_CONSOLE_UNLOCK () ; 
 int /*<<< orphan*/  ALTERA_JTAG_UART_CONTROL_AC ; 
 int /*<<< orphan*/  aju_cons_control_read () ; 
 int /*<<< orphan*/  aju_cons_control_write (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
aju_cninit(struct consdev *cp)
{
	uint32_t v;

	AJU_CONSOLE_LOCK_INIT();

	AJU_CONSOLE_LOCK();
	v = aju_cons_control_read();
	v &= ~ALTERA_JTAG_UART_CONTROL_AC;
	aju_cons_control_write(v);
	AJU_CONSOLE_UNLOCK();
}