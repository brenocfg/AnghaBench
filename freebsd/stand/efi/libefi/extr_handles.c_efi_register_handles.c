#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct entry {int dummy; } ;
struct devsw {int dummy; } ;
struct TYPE_5__ {int unit; struct devsw* dev; int /*<<< orphan*/ * alias; void* handle; } ;
typedef  void* EFI_HANDLE ;

/* Variables and functions */
 TYPE_1__* entry ; 
 TYPE_1__* malloc (size_t) ; 
 int nentries ; 
 TYPE_1__* realloc (TYPE_1__*,size_t) ; 

int
efi_register_handles(struct devsw *sw, EFI_HANDLE *handles,
    EFI_HANDLE *aliases, int count)
{
	size_t sz;
	int idx, unit;

	idx = nentries;
	nentries += count;
	sz = nentries * sizeof(struct entry);
	entry = (entry == NULL) ? malloc(sz) : realloc(entry, sz);
	for (unit = 0; idx < nentries; idx++, unit++) {
		entry[idx].handle = handles[unit];
		if (aliases != NULL)
			entry[idx].alias = aliases[unit];
		else
			entry[idx].alias = NULL;
		entry[idx].dev = sw;
		entry[idx].unit = unit;
	}
	return (0);
}