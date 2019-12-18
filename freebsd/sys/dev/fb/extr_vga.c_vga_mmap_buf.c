#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_paddr_t ;
typedef  scalar_t__ vm_ooffset_t ;
typedef  int /*<<< orphan*/  vm_memattr_t ;
struct TYPE_4__ {int vi_flags; scalar_t__ vi_window; } ;
struct TYPE_5__ {scalar_t__ va_window_size; TYPE_1__ va_info; } ;
typedef  TYPE_2__ video_adapter_t ;
typedef  int /*<<< orphan*/  uintmax_t ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int V_INFO_LINEAR ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vga_mmap_buf(video_adapter_t *adp, vm_ooffset_t offset, vm_paddr_t *paddr,
   	     int prot, vm_memattr_t *memattr)
{
    if (adp->va_info.vi_flags & V_INFO_LINEAR)
	return -1;

#if VGA_DEBUG > 0
    printf("vga_mmap_buf(): window:0x%jx, offset:0x%jx\n", 
	   (uintmax_t)adp->va_info.vi_window, (uintmax_t)offset);
#endif

    /* XXX: is this correct? */
    if (offset > adp->va_window_size - PAGE_SIZE)
	return -1;

    *paddr = adp->va_info.vi_window + offset;
    return 0;
}