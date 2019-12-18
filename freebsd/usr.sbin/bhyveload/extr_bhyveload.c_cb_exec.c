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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  BSP ; 
 int /*<<< orphan*/  USERBOOT_EXIT_QUIT ; 
 int /*<<< orphan*/  cb_exit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ cr3 ; 
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  gdtbase ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  rsp ; 
 int vm_setup_freebsd_registers (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vm_setup_freebsd_registers_i386 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cb_exec(void *arg, uint64_t rip)
{
	int error;

	if (cr3 == 0)
		error = vm_setup_freebsd_registers_i386(ctx, BSP, rip, gdtbase,
		    rsp);
	else
		error = vm_setup_freebsd_registers(ctx, BSP, rip, cr3, gdtbase,
		    rsp);
	if (error) {
		perror("vm_setup_freebsd_registers");
		cb_exit(NULL, USERBOOT_EXIT_QUIT);
	}

	cb_exit(NULL, 0);
}