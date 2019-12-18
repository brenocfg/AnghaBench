#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct ISCI_REQUEST {int index; int /*<<< orphan*/ * queued_ccb_in_progress; void* release_queued_ccb; int /*<<< orphan*/  queued_ccbs; int /*<<< orphan*/  pending_device_reset_element; scalar_t__ frozen_lun_mask; void* is_resetting; } ;
struct ISCI_REMOTE_DEVICE {int index; int /*<<< orphan*/ * queued_ccb_in_progress; void* release_queued_ccb; int /*<<< orphan*/  queued_ccbs; int /*<<< orphan*/  pending_device_reset_element; scalar_t__ frozen_lun_mask; void* is_resetting; } ;
struct ISCI_MEMORY {int size; int /*<<< orphan*/  physical_address; scalar_t__ virtual_address; } ;
struct ISCI_CONTROLLER {int queue_depth; int /*<<< orphan*/  remote_device_pool; TYPE_2__* domain; int /*<<< orphan*/ ** remote_device; int /*<<< orphan*/ * remote_device_memory; int /*<<< orphan*/  request_pool; int /*<<< orphan*/  buffer_dma_tag; int /*<<< orphan*/  scif_controller_handle; int /*<<< orphan*/  lock; int /*<<< orphan*/  mdl; struct ISCI_MEMORY request_memory; struct ISCI_MEMORY cached_controller_memory; struct ISCI_MEMORY uncached_controller_memory; TYPE_1__* isci; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  bus_addr_t ;
struct TYPE_4__ {struct ISCI_REQUEST* da_remote_device; } ;
struct TYPE_3__ {int /*<<< orphan*/  device; } ;
typedef  scalar_t__ POINTER_UINT ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 void* FALSE ; 
 int /*<<< orphan*/  ISCI_DMA_BOUNDARY ; 
 int /*<<< orphan*/  M_ISCI ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int SCI_MAX_DOMAINS ; 
 int SCI_MAX_REMOTE_DEVICES ; 
 int /*<<< orphan*/  SCI_MAX_SCATTER_GATHER_ELEMENTS ; 
 int SCI_MDE_ATTRIBUTE_CACHEABLE ; 
 int SCI_MDE_ATTRIBUTE_PHYSICALLY_CONTIGUOUS ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TUNABLE_INT_FETCH (char*,int*) ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  busdma_lock_mutex ; 
 int isci_allocate_dma_buffer (int /*<<< orphan*/ ,struct ISCI_CONTROLLER*,struct ISCI_MEMORY*) ; 
 int isci_io_request_get_max_io_size () ; 
 int isci_io_request_get_object_size () ; 
 int /*<<< orphan*/  isci_request_construct (struct ISCI_REQUEST*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ isci_request_get_object_size () ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sci_controller_get_memory_descriptor_list_handle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_fast_list_element_init (struct ISCI_REQUEST*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sci_mdl_decorator_assign_memory (int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ) ; 
 void* sci_mdl_decorator_get_memory_size (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sci_pool_initialize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_pool_put (int /*<<< orphan*/ ,struct ISCI_REQUEST*) ; 
 int scif_remote_device_get_object_size () ; 

int isci_controller_allocate_memory(struct ISCI_CONTROLLER *controller)
{
	int error;
	device_t device =  controller->isci->device;
	uint32_t max_segment_size = isci_io_request_get_max_io_size();
	uint32_t status = 0;
	struct ISCI_MEMORY *uncached_controller_memory =
	    &controller->uncached_controller_memory;
	struct ISCI_MEMORY *cached_controller_memory =
	    &controller->cached_controller_memory;
	struct ISCI_MEMORY *request_memory =
	    &controller->request_memory;
	POINTER_UINT virtual_address;
	bus_addr_t physical_address;

	controller->mdl = sci_controller_get_memory_descriptor_list_handle(
	    controller->scif_controller_handle);

	uncached_controller_memory->size = sci_mdl_decorator_get_memory_size(
	    controller->mdl, SCI_MDE_ATTRIBUTE_PHYSICALLY_CONTIGUOUS);

	error = isci_allocate_dma_buffer(device, controller,
	    uncached_controller_memory);

	if (error != 0)
	    return (error);

	sci_mdl_decorator_assign_memory( controller->mdl,
	    SCI_MDE_ATTRIBUTE_PHYSICALLY_CONTIGUOUS,
	    uncached_controller_memory->virtual_address,
	    uncached_controller_memory->physical_address);

	cached_controller_memory->size = sci_mdl_decorator_get_memory_size(
	    controller->mdl,
	    SCI_MDE_ATTRIBUTE_CACHEABLE | SCI_MDE_ATTRIBUTE_PHYSICALLY_CONTIGUOUS
	);

	error = isci_allocate_dma_buffer(device, controller,
	    cached_controller_memory);

	if (error != 0)
	    return (error);

	sci_mdl_decorator_assign_memory(controller->mdl,
	    SCI_MDE_ATTRIBUTE_CACHEABLE | SCI_MDE_ATTRIBUTE_PHYSICALLY_CONTIGUOUS,
	    cached_controller_memory->virtual_address,
	    cached_controller_memory->physical_address);

	request_memory->size =
	    controller->queue_depth * isci_io_request_get_object_size();

	error = isci_allocate_dma_buffer(device, controller, request_memory);

	if (error != 0)
	    return (error);

	/* For STP PIO testing, we want to ensure we can force multiple SGLs
	 *  since this has been a problem area in SCIL.  This tunable parameter
	 *  will allow us to force DMA segments to a smaller size, ensuring
	 *  that even if a physically contiguous buffer is attached to this
	 *  I/O, the DMA subsystem will pass us multiple segments in our DMA
	 *  load callback.
	 */
	TUNABLE_INT_FETCH("hw.isci.max_segment_size", &max_segment_size);

	/* Create DMA tag for our I/O requests.  Then we can create DMA maps based off
	 *  of this tag and store them in each of our ISCI_IO_REQUEST objects.  This
	 *  will enable better performance than creating the DMA maps every time we get
	 *  an I/O.
	 */
	status = bus_dma_tag_create(bus_get_dma_tag(device), 0x1,
	    ISCI_DMA_BOUNDARY, BUS_SPACE_MAXADDR, BUS_SPACE_MAXADDR,
	    NULL, NULL, isci_io_request_get_max_io_size(),
	    SCI_MAX_SCATTER_GATHER_ELEMENTS, max_segment_size, 0,
	    busdma_lock_mutex, &controller->lock,
	    &controller->buffer_dma_tag);

	sci_pool_initialize(controller->request_pool);

	virtual_address = request_memory->virtual_address;
	physical_address = request_memory->physical_address;

	for (int i = 0; i < controller->queue_depth; i++) {
		struct ISCI_REQUEST *request =
		    (struct ISCI_REQUEST *)virtual_address;

		isci_request_construct(request,
		    controller->scif_controller_handle,
		    controller->buffer_dma_tag, physical_address);

		sci_pool_put(controller->request_pool, request);

		virtual_address += isci_request_get_object_size();
		physical_address += isci_request_get_object_size();
	}

	uint32_t remote_device_size = sizeof(struct ISCI_REMOTE_DEVICE) +
	    scif_remote_device_get_object_size();

	controller->remote_device_memory = (uint8_t *) malloc(
	    remote_device_size * SCI_MAX_REMOTE_DEVICES, M_ISCI,
	    M_NOWAIT | M_ZERO);

	sci_pool_initialize(controller->remote_device_pool);

	uint8_t *remote_device_memory_ptr = controller->remote_device_memory;

	for (int i = 0; i < SCI_MAX_REMOTE_DEVICES; i++) {
		struct ISCI_REMOTE_DEVICE *remote_device =
		    (struct ISCI_REMOTE_DEVICE *)remote_device_memory_ptr;

		controller->remote_device[i] = NULL;
		remote_device->index = i;
		remote_device->is_resetting = FALSE;
		remote_device->frozen_lun_mask = 0;
		sci_fast_list_element_init(remote_device,
		    &remote_device->pending_device_reset_element);
		TAILQ_INIT(&remote_device->queued_ccbs);
		remote_device->release_queued_ccb = FALSE;
		remote_device->queued_ccb_in_progress = NULL;

		/*
		 * For the first SCI_MAX_DOMAINS device objects, do not put
		 *  them in the pool, rather assign them to each domain.  This
		 *  ensures that any device attached directly to port "i" will
		 *  always get CAM target id "i".
		 */
		if (i < SCI_MAX_DOMAINS)
			controller->domain[i].da_remote_device = remote_device;
		else
			sci_pool_put(controller->remote_device_pool,
			    remote_device);
		remote_device_memory_ptr += remote_device_size;
	}

	return (0);
}