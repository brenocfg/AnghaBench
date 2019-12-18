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
struct hdac_dma {int /*<<< orphan*/  dma_paddr; } ;
struct TYPE_3__ {int /*<<< orphan*/  ds_addr; } ;
typedef  TYPE_1__ bus_dma_segment_t ;

/* Variables and functions */

__attribute__((used)) static void
hdac_dma_cb(void *callback_arg, bus_dma_segment_t *segs, int nseg, int error)
{
	struct hdac_dma *dma;

	if (error == 0) {
		dma = (struct hdac_dma *)callback_arg;
		dma->dma_paddr = segs[0].ds_addr;
	}
}