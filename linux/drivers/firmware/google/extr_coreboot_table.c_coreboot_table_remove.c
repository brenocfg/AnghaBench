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
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  coreboot_bus_type ; 

__attribute__((used)) static int coreboot_table_remove(struct platform_device *pdev)
{
	bus_unregister(&coreboot_bus_type);
	return 0;
}