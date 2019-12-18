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
struct TYPE_3__ {int /*<<< orphan*/  ds_addr; } ;
typedef  TYPE_1__ bus_dma_segment_t ;
typedef  int /*<<< orphan*/  bus_addr_t ;
typedef  int /*<<< orphan*/  TW_VOID ;
typedef  int /*<<< orphan*/  TW_INT32 ;

/* Variables and functions */

__attribute__((used)) static TW_VOID
twa_map_load_callback(TW_VOID *arg, bus_dma_segment_t *segs,
	TW_INT32 nsegments, TW_INT32 error)
{
	*((bus_addr_t *)arg) = segs[0].ds_addr;
}