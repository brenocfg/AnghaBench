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
struct acpi_video_output {scalar_t__ handle; int vo_numlevels; int* vo_levels; int vo_brightness; } ;
typedef  int UINT32 ;
typedef  scalar_t__ ACPI_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_SERIAL_BEGIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_SERIAL_END (int /*<<< orphan*/ ) ; 
#define  VID_NOTIFY_CYCLE_BRN 131 
#define  VID_NOTIFY_DEC_BRN 130 
#define  VID_NOTIFY_INC_BRN 129 
#define  VID_NOTIFY_ZERO_BRN 128 
 char* acpi_name (scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,int,char*) ; 
 int /*<<< orphan*/  video_output ; 
 int vo_get_brightness (scalar_t__) ; 
 int /*<<< orphan*/  vo_set_brightness (scalar_t__,int) ; 

__attribute__((used)) static void
acpi_video_vo_notify_handler(ACPI_HANDLE handle, UINT32 notify, void *context)
{
	struct acpi_video_output *vo;
	int i, j, level, new_level;

	vo = context;
	ACPI_SERIAL_BEGIN(video_output);
	if (vo->handle != handle)
		goto out;

	switch (notify) {
	case VID_NOTIFY_CYCLE_BRN:
		if (vo->vo_numlevels <= 3)
			goto out;
		/* FALLTHROUGH */
	case VID_NOTIFY_INC_BRN:
	case VID_NOTIFY_DEC_BRN:
	case VID_NOTIFY_ZERO_BRN:
		if (vo->vo_levels == NULL)
			goto out;
		level = vo_get_brightness(handle);
		if (level < 0)
			goto out;
		break;
	default:
		printf("unknown notify event 0x%x from %s\n",
		    notify, acpi_name(handle));
		goto out;
	}

	new_level = level;
	switch (notify) {
	case VID_NOTIFY_CYCLE_BRN:
		for (i = 2; i < vo->vo_numlevels; i++)
			if (vo->vo_levels[i] == level) {
				new_level = vo->vo_numlevels > i + 1 ?
				     vo->vo_levels[i + 1] : vo->vo_levels[2];
				break;
			}
		break;
	case VID_NOTIFY_INC_BRN:
	case VID_NOTIFY_DEC_BRN:
		for (i = 0; i < vo->vo_numlevels; i++) {
			j = vo->vo_levels[i];
			if (notify == VID_NOTIFY_INC_BRN) {
				if (j > level &&
				    (j < new_level || level == new_level))
					new_level = j;
			} else {
				if (j < level &&
				    (j > new_level || level == new_level))
					new_level = j;
			}
		}
		break;
	case VID_NOTIFY_ZERO_BRN:
		for (i = 0; i < vo->vo_numlevels; i++)
			if (vo->vo_levels[i] == 0) {
				new_level = 0;
				break;
			}
		break;
	}
	if (new_level != level) {
		vo_set_brightness(handle, new_level);
		vo->vo_brightness = new_level;
	}

out:
	ACPI_SERIAL_END(video_output);
}