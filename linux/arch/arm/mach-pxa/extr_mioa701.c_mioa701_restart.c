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
 int /*<<< orphan*/  REBOOT_SOFT ; 
 int /*<<< orphan*/  mioa701_machine_exit () ; 
 int /*<<< orphan*/  pxa_restart (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void mioa701_restart(enum reboot_mode c, const char *cmd)
{
	mioa701_machine_exit();
	pxa_restart(REBOOT_SOFT, cmd);
}