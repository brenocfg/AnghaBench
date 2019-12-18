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
typedef  int u8 ;

/* Variables and functions */
 int /*<<< orphan*/  REG_CSCDR ; 
 int /*<<< orphan*/  REG_CSCIR ; 
 int inb_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  outb_p (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int elanfreq_get_cpu_frequency(unsigned int cpu)
{
	u8 clockspeed_reg;    /* Clock Speed Register */

	local_irq_disable();
	outb_p(0x80, REG_CSCIR);
	clockspeed_reg = inb_p(REG_CSCDR);
	local_irq_enable();

	if ((clockspeed_reg & 0xE0) == 0xE0)
		return 0;

	/* Are we in CPU clock multiplied mode (66/99 MHz)? */
	if ((clockspeed_reg & 0xE0) == 0xC0) {
		if ((clockspeed_reg & 0x01) == 0)
			return 66000;
		else
			return 99000;
	}

	/* 33 MHz is not 32 MHz... */
	if ((clockspeed_reg & 0xE0) == 0xA0)
		return 33000;

	return (1<<((clockspeed_reg & 0xE0) >> 5)) * 1000;
}