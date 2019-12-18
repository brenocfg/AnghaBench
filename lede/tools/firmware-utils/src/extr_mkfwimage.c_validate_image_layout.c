#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ st_size; } ;
struct TYPE_5__ {scalar_t__ partition_length; TYPE_4__ stats; int /*<<< orphan*/  filename; int /*<<< orphan*/  partition_name; } ;
typedef  TYPE_1__ part_data_t ;
struct TYPE_6__ {int part_count; TYPE_1__* parts; } ;
typedef  TYPE_2__ image_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR (char*,int,...) ; 
 int MAX_SECTIONS ; 
 scalar_t__ stat (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int validate_image_layout(image_info_t* im)
{
	int i;

	if (im->part_count == 0 || im->part_count > MAX_SECTIONS)
	{
		ERROR("Invalid part count '%d'\n", im->part_count);
		return -1;
	}

	for (i = 0; i < im->part_count; ++i)
	{
		part_data_t* d = &im->parts[i];
		int len = strlen(d->partition_name);
		if (len == 0 || len > 16)
		{
			ERROR("Invalid partition name '%s' of the part %d\n",
					d->partition_name, i);
			return -1;
		}
		if (stat(d->filename, &d->stats) < 0)
		{
			ERROR("Couldn't stat file '%s' from part '%s'\n",
				       	d->filename, d->partition_name);
			return -2;
		}
		if (d->stats.st_size == 0)
		{
			ERROR("File '%s' from part '%s' is empty!\n",
				       	d->filename, d->partition_name);
			return -3;
		}
		if (d->stats.st_size > d->partition_length) {
			ERROR("File '%s' too big (%d) - max size: 0x%08X (exceeds %lu bytes)\n",
				       	d->filename, i, d->partition_length,
					d->stats.st_size - d->partition_length);
			return -4;
		}
	}

	return 0;
}