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
struct gio_device_id {int id; } ;
struct TYPE_2__ {int id; } ;
struct gio_device {TYPE_1__ id; } ;

/* Variables and functions */

const struct gio_device_id *gio_match_device(const struct gio_device_id *match,
		     const struct gio_device *dev)
{
	const struct gio_device_id *ids;

	for (ids = match; ids->id != 0xff; ids++)
		if (ids->id == dev->id.id)
			return ids;

	return NULL;
}