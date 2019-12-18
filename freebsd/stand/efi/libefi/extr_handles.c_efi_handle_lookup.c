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
struct TYPE_2__ {scalar_t__ handle; scalar_t__ alias; int unit; int /*<<< orphan*/  extra; struct devsw* dev; } ;
typedef  scalar_t__ EFI_HANDLE ;

/* Variables and functions */
 int ENOENT ; 
 TYPE_1__* entry ; 
 int nentries ; 

int
efi_handle_lookup(EFI_HANDLE h, struct devsw **dev, int *unit, uint64_t *extra)
{
	int idx;

	for (idx = 0; idx < nentries; idx++) {
		if (entry[idx].handle != h && entry[idx].alias != h)
			continue;
		if (dev != NULL)
			*dev = entry[idx].dev;
		if (unit != NULL)
			*unit = entry[idx].unit;
		if (extra != NULL)
			*extra = entry[idx].extra;
		return (0);
	}
	return (ENOENT);
}