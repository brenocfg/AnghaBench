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
struct devsw {int dummy; } ;
struct TYPE_2__ {int unit; int /*<<< orphan*/ * handle; struct devsw* dev; } ;
typedef  int /*<<< orphan*/ * EFI_HANDLE ;

/* Variables and functions */
 TYPE_1__* entry ; 
 int nentries ; 

EFI_HANDLE
efi_find_handle(struct devsw *dev, int unit)
{
	int idx;

	for (idx = 0; idx < nentries; idx++) {
		if (entry[idx].dev != dev)
			continue;
		if (entry[idx].unit != unit)
			continue;
		return (entry[idx].handle);
	}
	return (NULL);
}