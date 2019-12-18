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
struct acpi_device_scan_ctx {scalar_t__ parent; int /*<<< orphan*/  arg; int /*<<< orphan*/  (* user_fn ) (scalar_t__,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/ * device_t ;
typedef  int /*<<< orphan*/  UINT32 ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  scalar_t__ ACPI_OBJECT_TYPE ;
typedef  scalar_t__ ACPI_HANDLE ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_TYPE_DEVICE ; 
 scalar_t__ ACPI_TYPE_POWER ; 
 scalar_t__ ACPI_TYPE_PROCESSOR ; 
 scalar_t__ ACPI_TYPE_THERMAL ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiAttachData (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiDetachData (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiGetType (scalar_t__,scalar_t__*) ; 
 scalar_t__ acpi_avoid (scalar_t__) ; 
 int /*<<< orphan*/  acpi_fake_objhandler ; 
 int /*<<< orphan*/ * acpi_get_device (scalar_t__) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (scalar_t__,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ACPI_STATUS
acpi_device_scan_cb(ACPI_HANDLE h, UINT32 level, void *arg, void **retval)
{
    struct acpi_device_scan_ctx *ctx;
    device_t dev, old_dev;
    ACPI_STATUS status;
    ACPI_OBJECT_TYPE type;

    /*
     * Skip this device if we think we'll have trouble with it or it is
     * the parent where the scan began.
     */
    ctx = (struct acpi_device_scan_ctx *)arg;
    if (acpi_avoid(h) || h == ctx->parent)
	return (AE_OK);

    /* If this is not a valid device type (e.g., a method), skip it. */
    if (ACPI_FAILURE(AcpiGetType(h, &type)))
	return (AE_OK);
    if (type != ACPI_TYPE_DEVICE && type != ACPI_TYPE_PROCESSOR &&
	type != ACPI_TYPE_THERMAL && type != ACPI_TYPE_POWER)
	return (AE_OK);

    /*
     * Call the user function with the current device.  If it is unchanged
     * afterwards, return.  Otherwise, we update the handle to the new dev.
     */
    old_dev = acpi_get_device(h);
    dev = old_dev;
    status = ctx->user_fn(h, &dev, level, ctx->arg);
    if (ACPI_FAILURE(status) || old_dev == dev)
	return (status);

    /* Remove the old child and its connection to the handle. */
    if (old_dev != NULL) {
	device_delete_child(device_get_parent(old_dev), old_dev);
	AcpiDetachData(h, acpi_fake_objhandler);
    }

    /* Recreate the handle association if the user created a device. */
    if (dev != NULL)
	AcpiAttachData(h, acpi_fake_objhandler, dev);

    return (AE_OK);
}