#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_paddr_t ;
typedef  scalar_t__ vm_ooffset_t ;
typedef  int /*<<< orphan*/  vm_memattr_t ;
struct cdev {int dummy; } ;
struct TYPE_4__ {int mr_ndesc; TYPE_1__* mr_desc; } ;
struct TYPE_3__ {int mr_flags; scalar_t__ mr_base; scalar_t__ mr_len; } ;

/* Variables and functions */
 scalar_t__ CDEV_MINOR_MEM ; 
 int EFAULT ; 
 int MDF_ACTIVE ; 
 int MDF_ATTRMASK ; 
#define  MDF_UNCACHEABLE 131 
#define  MDF_WRITEBACK 130 
#define  MDF_WRITECOMBINE 129 
#define  MDF_WRITETHROUGH 128 
 int /*<<< orphan*/  VM_MEMATTR_UNCACHEABLE ; 
 int /*<<< orphan*/  VM_MEMATTR_WRITE_BACK ; 
 int /*<<< orphan*/  VM_MEMATTR_WRITE_COMBINING ; 
 int /*<<< orphan*/  VM_MEMATTR_WRITE_THROUGH ; 
 scalar_t__ dev2unit (struct cdev*) ; 
 TYPE_2__ mem_range_softc ; 

int
memmmap(struct cdev *dev, vm_ooffset_t offset, vm_paddr_t *paddr,
    int prot, vm_memattr_t *memattr)
{
	int i;

	if (dev2unit(dev) == CDEV_MINOR_MEM)
		*paddr = offset;
	else
		return (EFAULT);

	for (i = 0; i < mem_range_softc.mr_ndesc; i++) {
		if (!(mem_range_softc.mr_desc[i].mr_flags & MDF_ACTIVE))
			continue;

		if (offset >= mem_range_softc.mr_desc[i].mr_base &&
		    offset < mem_range_softc.mr_desc[i].mr_base +
		    mem_range_softc.mr_desc[i].mr_len) {
			switch (mem_range_softc.mr_desc[i].mr_flags &
			    MDF_ATTRMASK) {
			case MDF_WRITEBACK:
				*memattr = VM_MEMATTR_WRITE_BACK;
				break;
			case MDF_WRITECOMBINE:
				*memattr = VM_MEMATTR_WRITE_COMBINING;
				break;
			case MDF_UNCACHEABLE:
				*memattr = VM_MEMATTR_UNCACHEABLE;
				break;
			case MDF_WRITETHROUGH:
				*memattr = VM_MEMATTR_WRITE_THROUGH;
				break;
			}

			break;
		}
	}

	return (0);
}