#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t vm_paddr_t ;
typedef  scalar_t__ off_t ;
struct TYPE_3__ {scalar_t__ ds_len; scalar_t__ ds_addr; } ;
typedef  TYPE_1__ bus_dma_segment_t ;

/* Variables and functions */
 size_t MIN (scalar_t__,size_t) ; 
 int physcopyout (size_t,void*,size_t) ; 

int
physcopyout_vlist(vm_paddr_t src, bus_dma_segment_t *dst, off_t offset,
    size_t len)
{
	size_t seg_len;
	int error;

	error = 0;
	while (offset >= dst->ds_len) {
		offset -= dst->ds_len;
		dst++;
	}

	while (len > 0 && error == 0) {
		seg_len = MIN(dst->ds_len - offset, len);
		error = physcopyout(src, (void *)(uintptr_t)(dst->ds_addr +
		    offset), seg_len);
		offset = 0;
		dst++;
		len -= seg_len;
		src += seg_len;
	}

	return (error);
}