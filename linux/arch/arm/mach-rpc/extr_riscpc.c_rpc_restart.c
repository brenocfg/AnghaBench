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
typedef  enum reboot_mode { ____Placeholder_reboot_mode } reboot_mode ;

/* Variables and functions */
 int /*<<< orphan*/  IOMD_ROMCR0 ; 
 int /*<<< orphan*/  iomd_writeb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soft_restart (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rpc_restart(enum reboot_mode mode, const char *cmd)
{
	iomd_writeb(0, IOMD_ROMCR0);

	/*
	 * Jump into the ROM
	 */
	soft_restart(0);
}