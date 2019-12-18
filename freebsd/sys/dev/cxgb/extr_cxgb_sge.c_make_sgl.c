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
struct sg_ent {scalar_t__* addr; scalar_t__* len; } ;
struct TYPE_3__ {scalar_t__ ds_len; int /*<<< orphan*/  ds_addr; } ;
typedef  TYPE_1__ bus_dma_segment_t ;

/* Variables and functions */
 scalar_t__ htobe32 (scalar_t__) ; 
 scalar_t__ htobe64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline void
make_sgl(struct sg_ent *sgp, bus_dma_segment_t *segs, int nsegs)
{
	int i, idx;
	
	for (idx = 0, i = 0; i < nsegs; i++) {
		/*
		 * firmware doesn't like empty segments
		 */
		if (segs[i].ds_len == 0)
			continue;
		if (i && idx == 0) 
			++sgp;
		
		sgp->len[idx] = htobe32(segs[i].ds_len);
		sgp->addr[idx] = htobe64(segs[i].ds_addr);
		idx ^= 1;
	}
	
	if (idx) {
		sgp->len[idx] = 0;
		sgp->addr[idx] = 0;
	}
}