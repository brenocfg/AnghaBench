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
#define  BOOT_ACPI 134 
#define  BOOT_BIOS 133 
#define  BOOT_CF9_FORCE 132 
#define  BOOT_CF9_SAFE 131 
#define  BOOT_EFI 130 
#define  BOOT_KBD 129 
#define  BOOT_TRIPLE 128 
 int /*<<< orphan*/  MRR_BIOS ; 
 scalar_t__ REBOOT_WARM ; 
 int /*<<< orphan*/  TB_SHUTDOWN_REBOOT ; 
 scalar_t__ __va (int) ; 
 int /*<<< orphan*/  acpi_reboot () ; 
 scalar_t__ efi_capsule_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efi_reboot (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emergency_vmx_disable_all () ; 
 int /*<<< orphan*/  idt_invalidate (int /*<<< orphan*/ *) ; 
 int inb (int) ; 
 int /*<<< orphan*/  kb_wait () ; 
 int /*<<< orphan*/  mach_reboot_fixups () ; 
 int /*<<< orphan*/  machine_real_restart (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int,int) ; 
 int port_cf9_safe ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 scalar_t__ reboot_emergency ; 
 scalar_t__ reboot_mode ; 
 int reboot_type ; 
 int /*<<< orphan*/  tboot_shutdown (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void native_machine_emergency_restart(void)
{
	int i;
	int attempt = 0;
	int orig_reboot_type = reboot_type;
	unsigned short mode;

	if (reboot_emergency)
		emergency_vmx_disable_all();

	tboot_shutdown(TB_SHUTDOWN_REBOOT);

	/* Tell the BIOS if we want cold or warm reboot */
	mode = reboot_mode == REBOOT_WARM ? 0x1234 : 0;
	*((unsigned short *)__va(0x472)) = mode;

	/*
	 * If an EFI capsule has been registered with the firmware then
	 * override the reboot= parameter.
	 */
	if (efi_capsule_pending(NULL)) {
		pr_info("EFI capsule is pending, forcing EFI reboot.\n");
		reboot_type = BOOT_EFI;
	}

	for (;;) {
		/* Could also try the reset bit in the Hammer NB */
		switch (reboot_type) {
		case BOOT_ACPI:
			acpi_reboot();
			reboot_type = BOOT_KBD;
			break;

		case BOOT_KBD:
			mach_reboot_fixups(); /* For board specific fixups */

			for (i = 0; i < 10; i++) {
				kb_wait();
				udelay(50);
				outb(0xfe, 0x64); /* Pulse reset low */
				udelay(50);
			}
			if (attempt == 0 && orig_reboot_type == BOOT_ACPI) {
				attempt = 1;
				reboot_type = BOOT_ACPI;
			} else {
				reboot_type = BOOT_EFI;
			}
			break;

		case BOOT_EFI:
			efi_reboot(reboot_mode, NULL);
			reboot_type = BOOT_BIOS;
			break;

		case BOOT_BIOS:
			machine_real_restart(MRR_BIOS);

			/* We're probably dead after this, but... */
			reboot_type = BOOT_CF9_SAFE;
			break;

		case BOOT_CF9_FORCE:
			port_cf9_safe = true;
			/* Fall through */

		case BOOT_CF9_SAFE:
			if (port_cf9_safe) {
				u8 reboot_code = reboot_mode == REBOOT_WARM ?  0x06 : 0x0E;
				u8 cf9 = inb(0xcf9) & ~reboot_code;
				outb(cf9|2, 0xcf9); /* Request hard reset */
				udelay(50);
				/* Actually do the reset */
				outb(cf9|reboot_code, 0xcf9);
				udelay(50);
			}
			reboot_type = BOOT_TRIPLE;
			break;

		case BOOT_TRIPLE:
			idt_invalidate(NULL);
			__asm__ __volatile__("int3");

			/* We're probably dead after this, but... */
			reboot_type = BOOT_KBD;
			break;
		}
	}
}