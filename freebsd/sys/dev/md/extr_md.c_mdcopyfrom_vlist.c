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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ off_t ;
struct TYPE_3__ {scalar_t__ ds_len; scalar_t__ ds_addr; } ;
typedef  TYPE_1__ bus_dma_segment_t ;

/* Variables and functions */
 int /*<<< orphan*/  bcopy (void*,void*,scalar_t__) ; 
 scalar_t__ omin (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
mdcopyfrom_vlist(bus_dma_segment_t *vlist, off_t offset, void *dst, off_t len)
{
	off_t seg_len;

	while (offset >= vlist->ds_len) {
		offset -= vlist->ds_len;
		vlist++;
	}

	while (len != 0) {
		seg_len = omin(len, vlist->ds_len - offset);
		bcopy((void *)(uintptr_t)(vlist->ds_addr + offset), dst,
		    seg_len);
		offset = 0;
		dst = (uint8_t *)dst + seg_len;
		len -= seg_len;
		vlist++;
	}
}