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
struct llan_softc {scalar_t__ filter_buf_phys; scalar_t__ input_buf_phys; scalar_t__ rx_buf_len; scalar_t__ rx_buf_phys; } ;
struct TYPE_3__ {scalar_t__ ds_len; scalar_t__ ds_addr; } ;
typedef  TYPE_1__ bus_dma_segment_t ;

/* Variables and functions */
 int PAGE_SIZE ; 

__attribute__((used)) static void
llan_rx_load_cb(void *xsc, bus_dma_segment_t *segs, int nsegs, int err)
{
	struct llan_softc *sc = xsc;

	sc->rx_buf_phys = segs[0].ds_addr;
	sc->rx_buf_len = segs[0].ds_len - 2*PAGE_SIZE;
	sc->input_buf_phys = segs[0].ds_addr + segs[0].ds_len - PAGE_SIZE;
	sc->filter_buf_phys = segs[0].ds_addr + segs[0].ds_len - 2*PAGE_SIZE;
}