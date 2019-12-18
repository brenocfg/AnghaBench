#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int _BQC_use_index; scalar_t__ _BCL_reversed; } ;
struct acpi_video_device_brightness {int* levels; unsigned long long count; TYPE_1__ flags; } ;
struct TYPE_4__ {scalar_t__ _BCQ; scalar_t__ _BQC; } ;
struct acpi_video_device {TYPE_2__ cap; struct acpi_video_device_brightness* brightness; } ;

/* Variables and functions */
 int ACPI_VIDEO_FIRST_LEVEL ; 
 int acpi_video_device_lcd_get_level_current (struct acpi_video_device*,unsigned long long*,int) ; 
 int acpi_video_device_lcd_set_level (struct acpi_video_device*,int) ; 
 scalar_t__ bqc_offset_aml_bug_workaround ; 

__attribute__((used)) static int acpi_video_bqc_quirk(struct acpi_video_device *device,
				int max_level, int current_level)
{
	struct acpi_video_device_brightness *br = device->brightness;
	int result;
	unsigned long long level;
	int test_level;

	/* don't mess with existing known broken systems */
	if (bqc_offset_aml_bug_workaround)
		return 0;

	/*
	 * Some systems always report current brightness level as maximum
	 * through _BQC, we need to test another value for them. However,
	 * there is a subtlety:
	 *
	 * If the _BCL package ordering is descending, the first level
	 * (br->levels[2]) is likely to be 0, and if the number of levels
	 * matches the number of steps, we might confuse a returned level to
	 * mean the index.
	 *
	 * For example:
	 *
	 *     current_level = max_level = 100
	 *     test_level = 0
	 *     returned level = 100
	 *
	 * In this case 100 means the level, not the index, and _BCM failed.
	 * Still, if the _BCL package ordering is descending, the index of
	 * level 0 is also 100, so we assume _BQC is indexed, when it's not.
	 *
	 * This causes all _BQC calls to return bogus values causing weird
	 * behavior from the user's perspective.  For example:
	 *
	 * xbacklight -set 10; xbacklight -set 20;
	 *
	 * would flash to 90% and then slowly down to the desired level (20).
	 *
	 * The solution is simple; test anything other than the first level
	 * (e.g. 1).
	 */
	test_level = current_level == max_level
		? br->levels[ACPI_VIDEO_FIRST_LEVEL + 1]
		: max_level;

	result = acpi_video_device_lcd_set_level(device, test_level);
	if (result)
		return result;

	result = acpi_video_device_lcd_get_level_current(device, &level, true);
	if (result)
		return result;

	if (level != test_level) {
		/* buggy _BQC found, need to find out if it uses index */
		if (level < br->count) {
			if (br->flags._BCL_reversed)
				level = br->count - ACPI_VIDEO_FIRST_LEVEL - 1 - level;
			if (br->levels[level + ACPI_VIDEO_FIRST_LEVEL] == test_level)
				br->flags._BQC_use_index = 1;
		}

		if (!br->flags._BQC_use_index)
			device->cap._BQC = device->cap._BCQ = 0;
	}

	return 0;
}