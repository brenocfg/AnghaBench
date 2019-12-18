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
struct ISCI_MEMORY {int error; int /*<<< orphan*/  physical_address; } ;
struct TYPE_3__ {int /*<<< orphan*/  ds_addr; } ;
typedef  TYPE_1__ bus_dma_segment_t ;

/* Variables and functions */
 int /*<<< orphan*/  isci_log_message (int /*<<< orphan*/ ,char*,char*) ; 

void
isci_allocate_dma_buffer_callback(void *arg, bus_dma_segment_t *seg,
    int nseg, int error)
{
	struct ISCI_MEMORY *memory = (struct ISCI_MEMORY *)arg;

	memory->error = error;

	if (nseg != 1 || error != 0)
		isci_log_message(0, "ISCI",
		    "Failed to allocate physically contiguous memory!\n");
	else
		memory->physical_address = seg->ds_addr;
}