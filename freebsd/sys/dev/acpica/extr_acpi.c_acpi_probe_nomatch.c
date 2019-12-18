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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_STATE_D3 ; 
 int /*<<< orphan*/  acpi_set_powerstate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
acpi_probe_nomatch(device_t bus, device_t child)
{
#ifdef ACPI_ENABLE_POWERDOWN_NODRIVER
    acpi_set_powerstate(child, ACPI_STATE_D3);
#endif
}