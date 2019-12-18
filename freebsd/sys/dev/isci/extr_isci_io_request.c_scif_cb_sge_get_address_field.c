#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ ds_addr; } ;
typedef  TYPE_1__ bus_dma_segment_t ;
typedef  int /*<<< orphan*/  SCI_PHYSICAL_ADDRESS ;

/* Variables and functions */

SCI_PHYSICAL_ADDRESS
scif_cb_sge_get_address_field(void *scif_user_io_request, void *sge_address)
{
	bus_dma_segment_t *sge = (bus_dma_segment_t *)sge_address;

	return ((SCI_PHYSICAL_ADDRESS)sge->ds_addr);
}