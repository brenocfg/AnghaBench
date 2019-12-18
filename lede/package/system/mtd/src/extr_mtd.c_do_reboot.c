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

/* Variables and functions */
 int /*<<< orphan*/  LINUX_REBOOT_CMD_RESTART ; 
 int /*<<< orphan*/  LINUX_REBOOT_MAGIC1 ; 
 int /*<<< orphan*/  LINUX_REBOOT_MAGIC2 ; 
 int /*<<< orphan*/  SYS_reboot ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  syscall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  system (char*) ; 

__attribute__((used)) static void do_reboot(void)
{
	fprintf(stderr, "Rebooting ...\n");
	fflush(stderr);

	/* try regular reboot method first */
	system("/sbin/reboot");
	sleep(2);

	/* if we're still alive at this point, force the kernel to reboot */
	syscall(SYS_reboot,LINUX_REBOOT_MAGIC1,LINUX_REBOOT_MAGIC2,LINUX_REBOOT_CMD_RESTART,NULL);
}