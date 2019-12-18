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
typedef  int /*<<< orphan*/  uint64_t ;
struct devsw {int dummy; } ;
struct TYPE_2__ {scalar_t__ handle; int unit; int /*<<< orphan*/  extra; int /*<<< orphan*/ * alias; struct devsw* dev; } ;
typedef  scalar_t__ EFI_HANDLE ;

/* Variables and functions */
 int ENOENT ; 
 TYPE_1__* entry ; 
 int nentries ; 

int
efi_handle_update_dev(EFI_HANDLE h, struct devsw *dev, int unit,
    uint64_t guid)
{
	int idx;

	for (idx = 0; idx < nentries; idx++) {
		if (entry[idx].handle != h)
			continue;
		entry[idx].dev = dev;
		entry[idx].unit = unit;
		entry[idx].alias = NULL;
		entry[idx].extra = guid;
		return (0);
	}

	return (ENOENT);
}