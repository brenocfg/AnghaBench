#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bus_size_t ;
typedef  int /*<<< orphan*/  bus_dmamap_t ;
typedef  int /*<<< orphan*/  (* bus_dmamap_callback_t ) (void*,TYPE_1__*,int,int /*<<< orphan*/ ) ;
typedef  int /*<<< orphan*/  bus_dma_tag_t ;
struct TYPE_5__ {uintptr_t ds_addr; int /*<<< orphan*/  ds_len; } ;
typedef  TYPE_1__ bus_dma_segment_t ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (void*,TYPE_1__*,int,int /*<<< orphan*/ ) ; 

int
bus_dmamap_load(bus_dma_tag_t dmat, bus_dmamap_t map, void *buf,
    bus_size_t buflen, bus_dmamap_callback_t *callback,
    void *callback_arg, int flags)
{
	bus_dma_segment_t segs[1];

	segs[0].ds_addr = (uintptr_t)buf;
	segs[0].ds_len = buflen;

	(*callback)(callback_arg, segs, 1, 0);

	return (0);
}