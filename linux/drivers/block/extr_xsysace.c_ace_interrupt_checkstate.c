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
typedef  int u32 ;
typedef  int u16 ;
struct ace_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACE_CTRL ; 
 int ACE_CTRL_ERRORIRQ ; 
 int /*<<< orphan*/  ACE_STATUS ; 
 int ACE_STATUS_CFCERROR ; 
 int ACE_STATUS_CFGERROR ; 
 int EIO ; 
 int /*<<< orphan*/  ace_dump_regs (struct ace_device*) ; 
 int ace_in (struct ace_device*,int /*<<< orphan*/ ) ; 
 int ace_in32 (struct ace_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int ace_interrupt_checkstate(struct ace_device *ace)
{
	u32 sreg = ace_in32(ace, ACE_STATUS);
	u16 creg = ace_in(ace, ACE_CTRL);

	/* Check for error occurrence */
	if ((sreg & (ACE_STATUS_CFGERROR | ACE_STATUS_CFCERROR)) &&
	    (creg & ACE_CTRL_ERRORIRQ)) {
		dev_err(ace->dev, "transfer failure\n");
		ace_dump_regs(ace);
		return -EIO;
	}

	return 0;
}