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
struct agp_memory_info {int /*<<< orphan*/  ami_is_bound; int /*<<< orphan*/  ami_offset; int /*<<< orphan*/  ami_physical; int /*<<< orphan*/  ami_size; } ;
struct agp_memory {int /*<<< orphan*/  am_is_bound; int /*<<< orphan*/  am_offset; int /*<<< orphan*/  am_physical; int /*<<< orphan*/  am_size; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */

void agp_memory_info(device_t dev, void *handle, struct
		     agp_memory_info *mi)
{
	struct agp_memory *mem = (struct agp_memory *) handle;

	mi->ami_size = mem->am_size;
	mi->ami_physical = mem->am_physical;
	mi->ami_offset = mem->am_offset;
	mi->ami_is_bound = mem->am_is_bound;
}