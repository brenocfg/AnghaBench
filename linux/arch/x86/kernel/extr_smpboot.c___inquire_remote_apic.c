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

/* Variables and functions */
 unsigned int APIC_DM_REMRD ; 
 int /*<<< orphan*/  APIC_ICR ; 
 int APIC_ICR_RR_INPROG ; 
 int APIC_ICR_RR_MASK ; 
#define  APIC_ICR_RR_VALID 128 
 int APIC_ID ; 
 int APIC_LVR ; 
 int /*<<< orphan*/  APIC_RRR ; 
 int APIC_SPIV ; 
 unsigned int ARRAY_SIZE (unsigned int*) ; 
 int /*<<< orphan*/  apic_icr_write (unsigned int,int) ; 
 int apic_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_cont (char*,...) ; 
 int /*<<< orphan*/  pr_info (char*,int,...) ; 
 int safe_apic_wait_icr_idle () ; 
 int /*<<< orphan*/  udelay (int) ; 

void __inquire_remote_apic(int apicid)
{
	unsigned i, regs[] = { APIC_ID >> 4, APIC_LVR >> 4, APIC_SPIV >> 4 };
	const char * const names[] = { "ID", "VERSION", "SPIV" };
	int timeout;
	u32 status;

	pr_info("Inquiring remote APIC 0x%x...\n", apicid);

	for (i = 0; i < ARRAY_SIZE(regs); i++) {
		pr_info("... APIC 0x%x %s: ", apicid, names[i]);

		/*
		 * Wait for idle.
		 */
		status = safe_apic_wait_icr_idle();
		if (status)
			pr_cont("a previous APIC delivery may have failed\n");

		apic_icr_write(APIC_DM_REMRD | regs[i], apicid);

		timeout = 0;
		do {
			udelay(100);
			status = apic_read(APIC_ICR) & APIC_ICR_RR_MASK;
		} while (status == APIC_ICR_RR_INPROG && timeout++ < 1000);

		switch (status) {
		case APIC_ICR_RR_VALID:
			status = apic_read(APIC_RRR);
			pr_cont("%08x\n", status);
			break;
		default:
			pr_cont("failed\n");
		}
	}
}