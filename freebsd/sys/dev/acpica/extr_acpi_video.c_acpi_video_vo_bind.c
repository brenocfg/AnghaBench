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
struct acpi_video_output {int* vo_levels; int vo_numlevels; int vo_fullpower; int vo_economy; int /*<<< orphan*/  handle; } ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DEVICE_NOTIFY ; 
 int /*<<< orphan*/  ACPI_SERIAL_BEGIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_SERIAL_END (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiInstallNotifyHandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_video_output*) ; 
 int /*<<< orphan*/  AcpiOsFree (int*) ; 
 int /*<<< orphan*/  AcpiRemoveNotifyHandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t BCL_ECONOMY ; 
 size_t BCL_FULLPOWER ; 
 scalar_t__ acpi_video_vo_check_level (struct acpi_video_output*,int) ; 
 int /*<<< orphan*/  acpi_video_vo_notify_handler ; 
 int /*<<< orphan*/  video_output ; 
 int vo_get_brightness_levels (int /*<<< orphan*/ ,int**) ; 

__attribute__((used)) static void
acpi_video_vo_bind(struct acpi_video_output *vo, ACPI_HANDLE handle)
{

	ACPI_SERIAL_BEGIN(video_output);
	if (vo->vo_levels != NULL) {
		AcpiRemoveNotifyHandler(vo->handle, ACPI_DEVICE_NOTIFY,
		    acpi_video_vo_notify_handler);
		AcpiOsFree(vo->vo_levels);
		vo->vo_levels = NULL;
	}
	vo->handle = handle;
	vo->vo_numlevels = vo_get_brightness_levels(handle, &vo->vo_levels);
	if (vo->vo_numlevels >= 2) {
		if (vo->vo_fullpower == -1 ||
		    acpi_video_vo_check_level(vo, vo->vo_fullpower) != 0) {
			/* XXX - can't deal with rebinding... */
			vo->vo_fullpower = vo->vo_levels[BCL_FULLPOWER];
		}
		if (vo->vo_economy == -1 ||
		    acpi_video_vo_check_level(vo, vo->vo_economy) != 0) {
			/* XXX - see above. */
			vo->vo_economy = vo->vo_levels[BCL_ECONOMY];
		}
		AcpiInstallNotifyHandler(handle, ACPI_DEVICE_NOTIFY,
		    acpi_video_vo_notify_handler, vo);
	}
	ACPI_SERIAL_END(video_output);
}