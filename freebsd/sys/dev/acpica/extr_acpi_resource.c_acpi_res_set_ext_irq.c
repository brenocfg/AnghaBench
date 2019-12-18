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
typedef  int /*<<< orphan*/  uint32_t ;
struct acpi_res_context {int /*<<< orphan*/  ar_nirq; } ;
typedef  int /*<<< orphan*/  rman_res_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_set_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
acpi_res_set_ext_irq(device_t dev, void *context, uint32_t *irq, int count,
    int trig, int pol)
{
    struct acpi_res_context	*cp = (struct acpi_res_context *)context;
    rman_res_t intr;

    if (cp == NULL || irq == NULL)
	return;

    /* This implements no resource relocation. */
    if (count != 1)
	return;

    intr = *irq;
    bus_set_resource(dev, SYS_RES_IRQ, cp->ar_nirq++, intr, 1);
}