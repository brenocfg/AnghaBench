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
struct intel_raid_conf {int total_disks; TYPE_1__* disk; } ;
struct TYPE_2__ {int /*<<< orphan*/  serial; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTEL_SERIAL_LEN ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
intel_meta_find_disk(struct intel_raid_conf *meta, char *serial)
{
	int pos;

	for (pos = 0; pos < meta->total_disks; pos++) {
		if (strncmp(meta->disk[pos].serial,
		    serial, INTEL_SERIAL_LEN) == 0)
			return (pos);
	}
	return (-1);
}