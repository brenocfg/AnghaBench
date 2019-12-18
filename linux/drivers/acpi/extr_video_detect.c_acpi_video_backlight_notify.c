#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct notifier_block {int dummy; } ;
struct TYPE_2__ {scalar_t__ type; } ;
struct backlight_device {TYPE_1__ props; } ;

/* Variables and functions */
 scalar_t__ BACKLIGHT_RAW ; 
 unsigned long BACKLIGHT_REGISTERED ; 
 int NOTIFY_OK ; 
 int /*<<< orphan*/  backlight_notify_work ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int acpi_video_backlight_notify(struct notifier_block *nb,
				       unsigned long val, void *bd)
{
	struct backlight_device *backlight = bd;

	/* A raw bl registering may change video -> native */
	if (backlight->props.type == BACKLIGHT_RAW &&
	    val == BACKLIGHT_REGISTERED)
		schedule_work(&backlight_notify_work);

	return NOTIFY_OK;
}