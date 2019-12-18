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
struct acpi_video_output {int* vo_levels; int vo_numlevels; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_SERIAL_ASSERT (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  video_output ; 

__attribute__((used)) static int
acpi_video_vo_check_level(struct acpi_video_output *vo, int level)
{
	int i;

	ACPI_SERIAL_ASSERT(video_output);
	if (vo->vo_levels == NULL)
		return (ENODEV);
	for (i = 0; i < vo->vo_numlevels; i++)
		if (vo->vo_levels[i] == level)
			return (0);
	return (EINVAL);
}