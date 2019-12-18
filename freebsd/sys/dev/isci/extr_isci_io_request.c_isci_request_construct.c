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
struct ISCI_REQUEST {int /*<<< orphan*/  timer; int /*<<< orphan*/  dma_map; int /*<<< orphan*/  dma_tag; int /*<<< orphan*/  physical_address; int /*<<< orphan*/  controller_handle; } ;
typedef  int /*<<< orphan*/  bus_dma_tag_t ;
typedef  int /*<<< orphan*/  bus_addr_t ;
typedef  int /*<<< orphan*/  SCI_CONTROLLER_HANDLE_T ;

/* Variables and functions */
 int /*<<< orphan*/  bus_dmamap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int) ; 

void
isci_request_construct(struct ISCI_REQUEST *request,
    SCI_CONTROLLER_HANDLE_T scif_controller_handle,
    bus_dma_tag_t io_buffer_dma_tag, bus_addr_t physical_address)
{

	request->controller_handle = scif_controller_handle;
	request->dma_tag = io_buffer_dma_tag;
	request->physical_address = physical_address;
	bus_dmamap_create(request->dma_tag, 0, &request->dma_map);
	callout_init(&request->timer, 1);
}