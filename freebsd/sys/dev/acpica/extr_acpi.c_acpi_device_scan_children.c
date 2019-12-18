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
struct acpi_device_scan_ctx {int /*<<< orphan*/ * parent; void* arg; int /*<<< orphan*/  user_fn; } ;
typedef  int /*<<< orphan*/ * device_t ;
typedef  int /*<<< orphan*/  acpi_scan_cb_t ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/ * ACPI_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/ * ACPI_ROOT_OBJECT ; 
 int /*<<< orphan*/  ACPI_TYPE_ANY ; 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiWalkNamespace (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct acpi_device_scan_ctx*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_device_scan_cb ; 
 scalar_t__ acpi_disabled (char*) ; 
 int /*<<< orphan*/ * acpi_get_handle (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ACPI_STATUS
acpi_device_scan_children(device_t bus, device_t dev, int max_depth,
    acpi_scan_cb_t user_fn, void *arg)
{
    ACPI_HANDLE h;
    struct acpi_device_scan_ctx ctx;

    if (acpi_disabled("children"))
	return (AE_OK);

    if (dev == NULL)
	h = ACPI_ROOT_OBJECT;
    else if ((h = acpi_get_handle(dev)) == NULL)
	return (AE_BAD_PARAMETER);
    ctx.user_fn = user_fn;
    ctx.arg = arg;
    ctx.parent = h;
    return (AcpiWalkNamespace(ACPI_TYPE_ANY, h, max_depth,
	acpi_device_scan_cb, NULL, &ctx, NULL));
}