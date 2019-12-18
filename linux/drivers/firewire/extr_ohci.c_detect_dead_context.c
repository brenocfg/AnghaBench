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
struct fw_ohci {int dummy; } ;

/* Variables and functions */
 int CONTEXT_DEAD ; 
 int /*<<< orphan*/  CONTROL_SET (unsigned int) ; 
 int /*<<< orphan*/ * evts ; 
 int /*<<< orphan*/  ohci_err (struct fw_ohci*,char*,char const*,int /*<<< orphan*/ ) ; 
 int reg_read (struct fw_ohci*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void detect_dead_context(struct fw_ohci *ohci,
				const char *name, unsigned int regs)
{
	u32 ctl;

	ctl = reg_read(ohci, CONTROL_SET(regs));
	if (ctl & CONTEXT_DEAD)
		ohci_err(ohci, "DMA context %s has stopped, error code: %s\n",
			name, evts[ctl & 0x1f]);
}