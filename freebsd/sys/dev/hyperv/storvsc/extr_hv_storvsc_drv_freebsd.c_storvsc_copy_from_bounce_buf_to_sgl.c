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
typedef  int uint64_t ;
struct sglist {TYPE_1__* sg_segs; } ;
struct TYPE_5__ {scalar_t__ ds_addr; } ;
typedef  TYPE_2__ bus_dma_segment_t ;
struct TYPE_4__ {int /*<<< orphan*/  ss_len; scalar_t__ ss_paddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,void*,int /*<<< orphan*/ ) ; 

void
storvsc_copy_from_bounce_buf_to_sgl(bus_dma_segment_t *dest_sgl,
				    unsigned int dest_sgl_count,
				    struct sglist* src_sgl,
				    uint64_t seg_bits)
{
	int sgl_idx = 0;
	
	for (sgl_idx = 0; sgl_idx < dest_sgl_count; sgl_idx++) {
		if (seg_bits & (1 << sgl_idx)) {
			memcpy((void*)(dest_sgl[sgl_idx].ds_addr),
			    (void*)(src_sgl->sg_segs[sgl_idx].ss_paddr),
			    src_sgl->sg_segs[sgl_idx].ss_len);
		}
	}
}