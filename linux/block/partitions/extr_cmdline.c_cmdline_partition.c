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
struct parsed_partitions {int /*<<< orphan*/  pp_buf; TYPE_1__* bdev; } ;
struct cmdline_parts {int dummy; } ;
typedef  int sector_t ;
struct TYPE_2__ {int /*<<< orphan*/  bd_disk; } ;

/* Variables and functions */
 int BDEVNAME_SIZE ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  add_part ; 
 scalar_t__ bdev_parts ; 
 int /*<<< orphan*/  bdevname (TYPE_1__*,char*) ; 
 int /*<<< orphan*/ * cmdline ; 
 struct cmdline_parts* cmdline_parts_find (scalar_t__,char*) ; 
 int /*<<< orphan*/  cmdline_parts_free (scalar_t__*) ; 
 scalar_t__ cmdline_parts_parse (scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmdline_parts_set (struct cmdline_parts*,int,int,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  cmdline_parts_verifier (int,struct parsed_partitions*) ; 
 int get_capacity (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcat (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int cmdline_partition(struct parsed_partitions *state)
{
	sector_t disk_size;
	char bdev[BDEVNAME_SIZE];
	struct cmdline_parts *parts;

	if (cmdline) {
		if (bdev_parts)
			cmdline_parts_free(&bdev_parts);

		if (cmdline_parts_parse(&bdev_parts, cmdline)) {
			cmdline = NULL;
			return -1;
		}
		cmdline = NULL;
	}

	if (!bdev_parts)
		return 0;

	bdevname(state->bdev, bdev);
	parts = cmdline_parts_find(bdev_parts, bdev);
	if (!parts)
		return 0;

	disk_size = get_capacity(state->bdev->bd_disk) << 9;

	cmdline_parts_set(parts, disk_size, 1, add_part, (void *)state);
	cmdline_parts_verifier(1, state);

	strlcat(state->pp_buf, "\n", PAGE_SIZE);

	return 1;
}