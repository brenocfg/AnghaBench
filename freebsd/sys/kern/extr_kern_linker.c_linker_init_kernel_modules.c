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
 int /*<<< orphan*/  kld_sx ; 
 int /*<<< orphan*/  linker_file_register_modules (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linker_kernel_file ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
linker_init_kernel_modules(void)
{

	sx_xlock(&kld_sx);
	linker_file_register_modules(linker_kernel_file);
	sx_xunlock(&kld_sx);
}