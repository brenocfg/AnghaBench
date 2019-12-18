#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_paddr_t ;
typedef  scalar_t__ vm_ooffset_t ;
typedef  int /*<<< orphan*/  vm_memattr_t ;
struct TYPE_7__ {scalar_t__ vi_buffer; int vi_flags; int /*<<< orphan*/  vi_window; } ;
struct TYPE_8__ {scalar_t__ va_window_size; TYPE_1__ va_info; } ;
typedef  TYPE_2__ video_adapter_t ;
struct TYPE_9__ {int (* mmap ) (TYPE_2__*,scalar_t__,scalar_t__*,int,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  VM_MEMATTR_WRITE_COMBINING ; 
 int V_INFO_LINEAR ; 
 TYPE_6__* prevvidsw ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int stub1 (TYPE_2__*,scalar_t__,scalar_t__*,int,int /*<<< orphan*/ *) ; 
 TYPE_2__* vesa_adp ; 

__attribute__((used)) static int
vesa_mmap(video_adapter_t *adp, vm_ooffset_t offset, vm_paddr_t *paddr,
	  int prot, vm_memattr_t *memattr)
{

#if VESA_DEBUG > 0
	printf("vesa_mmap(): window:0x%tx, buffer:0x%tx, offset:0x%jx\n", 
	       adp->va_info.vi_window, adp->va_info.vi_buffer, offset);
#endif

	if ((adp == vesa_adp) &&
	    (adp->va_info.vi_flags & V_INFO_LINEAR) != 0) {
		/* va_window_size == va_buffer_size/vi_planes */
		/* XXX: is this correct? */
		if (offset > adp->va_window_size - PAGE_SIZE)
			return (-1);
		*paddr = adp->va_info.vi_buffer + offset;
#ifdef VM_MEMATTR_WRITE_COMBINING
		*memattr = VM_MEMATTR_WRITE_COMBINING;
#endif
		return (0);
	}
	return ((*prevvidsw->mmap)(adp, offset, paddr, prot, memattr));
}