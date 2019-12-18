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
struct TYPE_5__ {int /*<<< orphan*/  ds_len; scalar_t__ ds_addr; } ;
typedef  TYPE_2__ bus_dma_segment_t ;
struct TYPE_4__ {int /*<<< orphan*/  ss_len; scalar_t__ ss_paddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
storvsc_copy_sgl_to_bounce_buf(struct sglist *bounce_sgl,
			       bus_dma_segment_t *orig_sgl,
			       unsigned int orig_sgl_count,
			       uint64_t seg_bits)
{
	int src_sgl_idx = 0;

	for (src_sgl_idx = 0; src_sgl_idx < orig_sgl_count; src_sgl_idx++) {
		if (seg_bits & (1 << src_sgl_idx)) {
			memcpy((void*)bounce_sgl->sg_segs[src_sgl_idx].ss_paddr,
			    (void*)orig_sgl[src_sgl_idx].ds_addr,
			    orig_sgl[src_sgl_idx].ds_len);

			bounce_sgl->sg_segs[src_sgl_idx].ss_len =
			    orig_sgl[src_sgl_idx].ds_len;
		}
	}
}