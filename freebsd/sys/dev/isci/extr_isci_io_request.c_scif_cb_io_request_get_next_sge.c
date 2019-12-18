#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ISCI_IO_REQUEST {size_t current_sge_index; size_t num_segments; int /*<<< orphan*/ * sge; } ;
typedef  int /*<<< orphan*/  bus_dma_segment_t ;

/* Variables and functions */

void
scif_cb_io_request_get_next_sge(void * scif_user_io_request,
    void * current_sge_address, void ** next_sge)
{
	struct ISCI_IO_REQUEST *isci_request =
	    (struct ISCI_IO_REQUEST *)scif_user_io_request;

	if (isci_request->current_sge_index == isci_request->num_segments)
		*next_sge = NULL;
	else {
		bus_dma_segment_t *sge =
		    &isci_request->sge[isci_request->current_sge_index];

		isci_request->current_sge_index++;
		*next_sge = sge;
	}
}