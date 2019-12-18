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
struct device_node {int dummy; } ;

/* Variables and functions */
 scalar_t__ WARN (int,char*) ; 
 struct device_node* of_find_compatible_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  of_iomap (struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wdt_regs ; 

__attribute__((used)) static void picoxcell_setup_restart(void)
{
	struct device_node *np = of_find_compatible_node(NULL, NULL,
							 "snps,dw-apb-wdg");
	if (WARN(!np, "unable to setup watchdog restart"))
		return;

	wdt_regs = of_iomap(np, 0);
	WARN(!wdt_regs, "failed to remap watchdog regs");
}