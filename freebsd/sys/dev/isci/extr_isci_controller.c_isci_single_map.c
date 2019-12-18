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
typedef  int /*<<< orphan*/  SCI_PHYSICAL_ADDRESS ;

/* Variables and functions */

__attribute__((used)) static void
isci_single_map(void *arg, bus_dma_segment_t *seg, int nseg, int error)
{
	SCI_PHYSICAL_ADDRESS *phys_addr = arg;

	*phys_addr = seg[0].ds_addr;
}