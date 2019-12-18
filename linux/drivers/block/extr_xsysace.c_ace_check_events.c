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
struct gendisk {struct ace_device* private_data; } ;
struct ace_device {scalar_t__ media_change; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int DISK_EVENT_MEDIA_CHANGE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static unsigned int ace_check_events(struct gendisk *gd, unsigned int clearing)
{
	struct ace_device *ace = gd->private_data;
	dev_dbg(ace->dev, "ace_check_events(): %i\n", ace->media_change);

	return ace->media_change ? DISK_EVENT_MEDIA_CHANGE : 0;
}