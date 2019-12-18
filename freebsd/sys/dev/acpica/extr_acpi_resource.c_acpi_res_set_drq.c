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
typedef  int /*<<< orphan*/  uint8_t ;
struct acpi_res_context {int /*<<< orphan*/  ar_ndrq; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_DRQ ; 
 int /*<<< orphan*/  bus_set_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
acpi_res_set_drq(device_t dev, void *context, uint8_t *drq, int count)
{
    struct acpi_res_context	*cp = (struct acpi_res_context *)context;

    if (cp == NULL || drq == NULL)
	return;
    
    /* This implements no resource relocation. */
    if (count != 1)
	return;

    bus_set_resource(dev, SYS_RES_DRQ, cp->ar_ndrq++, *drq, 1);
}