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
 int physcopyin (void*,size_t,size_t) ; 

int
physcopyin_vlist(bus_dma_segment_t *src, off_t offset, vm_paddr_t dst,
    size_t len)
{
	size_t seg_len;
	int error;

	error = 0;
	while (offset >= src->ds_len) {
		offset -= src->ds_len;
		src++;
	}

	while (len > 0 && error == 0) {
		seg_len = MIN(src->ds_len - offset, len);
		error = physcopyin((void *)(uintptr_t)(src->ds_addr + offset),
		    dst, seg_len);
		offset = 0;
		src++;
		len -= seg_len;
		dst += seg_len;
	}

	return (error);
}