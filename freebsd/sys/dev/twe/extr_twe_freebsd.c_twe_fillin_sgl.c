#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ ds_len; scalar_t__ ds_addr; } ;
typedef  TYPE_1__ bus_dma_segment_t ;
struct TYPE_6__ {scalar_t__ length; scalar_t__ address; } ;
typedef  TYPE_2__ TWE_SG_Entry ;

/* Variables and functions */

__attribute__((used)) static void
twe_fillin_sgl(TWE_SG_Entry *sgl, bus_dma_segment_t *segs, int nsegments, int max_sgl)
{
    int i;

    for (i = 0; i < nsegments; i++) {
	sgl[i].address = segs[i].ds_addr;
	sgl[i].length = segs[i].ds_len;
    }
    for (; i < max_sgl; i++) {				/* XXX necessary? */
	sgl[i].address = 0;
	sgl[i].length = 0;
    }
}