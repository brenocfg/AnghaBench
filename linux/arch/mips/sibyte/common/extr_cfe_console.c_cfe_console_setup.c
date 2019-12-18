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
struct console {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ cfe_getenv (char*,char*,int) ; 
 int /*<<< orphan*/  setleds (char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static int cfe_console_setup(struct console *cons, char *str)
{
	char consdev[32];
	/* XXXKW think about interaction with 'console=' cmdline arg */
	/* If none of the console options are configured, the build will break. */
	if (cfe_getenv("BOOT_CONSOLE", consdev, 32) >= 0) {
#ifdef CONFIG_SERIAL_SB1250_DUART
		if (!strcmp(consdev, "uart0")) {
			setleds("u0cn");
		} else if (!strcmp(consdev, "uart1")) {
			setleds("u1cn");
		} else
#endif
#ifdef CONFIG_VGA_CONSOLE
		       if (!strcmp(consdev, "pcconsole0")) {
				setleds("pccn");
		} else
#endif
			return -ENODEV;
	}
	return 0;
}