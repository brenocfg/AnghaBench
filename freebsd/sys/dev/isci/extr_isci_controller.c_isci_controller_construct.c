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
typedef  size_t uint32_t ;
struct isci_softc {int /*<<< orphan*/  sci_library_handle; } ;
struct ISCI_TIMER {int dummy; } ;
struct ISCI_CONTROLLER {int /*<<< orphan*/  unmap_buffer_pool; int /*<<< orphan*/  timer_pool; scalar_t__ timer_memory; int /*<<< orphan*/ * domain; int /*<<< orphan*/  lock; int /*<<< orphan*/  pending_device_reset_list; scalar_t__ initial_discovery_mask; int /*<<< orphan*/ * sim; void* release_queued_ccbs; void* is_frozen; void* is_started; int /*<<< orphan*/  scif_controller_handle; struct isci_softc* isci; } ;
typedef  int /*<<< orphan*/  SCI_CONTROLLER_HANDLE_T ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_ISCI ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 size_t SCI_MAX_DOMAINS ; 
 int SCI_MAX_TIMERS ; 
 int /*<<< orphan*/  isci_domain_construct (int /*<<< orphan*/ *,size_t,struct ISCI_CONTROLLER*) ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_fast_list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sci_object_set_association (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  sci_pool_initialize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_pool_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scif_controller_construct (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scif_library_allocate_controller (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void isci_controller_construct(struct ISCI_CONTROLLER *controller,
    struct isci_softc *isci)
{
	SCI_CONTROLLER_HANDLE_T scif_controller_handle;

	scif_library_allocate_controller(isci->sci_library_handle,
	    &scif_controller_handle);

	scif_controller_construct(isci->sci_library_handle,
	    scif_controller_handle, NULL);

	controller->isci = isci;
	controller->scif_controller_handle = scif_controller_handle;

	/* This allows us to later use
	 *  sci_object_get_association(scif_controller_handle)
	 * inside of a callback routine to get our struct ISCI_CONTROLLER object
	 */
	sci_object_set_association(scif_controller_handle, (void *)controller);

	controller->is_started = FALSE;
	controller->is_frozen = FALSE;
	controller->release_queued_ccbs = FALSE;
	controller->sim = NULL;
	controller->initial_discovery_mask = 0;

	sci_fast_list_init(&controller->pending_device_reset_list);

	mtx_init(&controller->lock, "isci", NULL, MTX_DEF);

	uint32_t domain_index;

	for(domain_index = 0; domain_index < SCI_MAX_DOMAINS; domain_index++) {
		isci_domain_construct( &controller->domain[domain_index],
		    domain_index, controller);
	}

	controller->timer_memory = malloc(
	    sizeof(struct ISCI_TIMER) * SCI_MAX_TIMERS, M_ISCI,
	    M_NOWAIT | M_ZERO);

	sci_pool_initialize(controller->timer_pool);

	struct ISCI_TIMER *timer = (struct ISCI_TIMER *)
	    controller->timer_memory;

	for ( int i = 0; i < SCI_MAX_TIMERS; i++ ) {
		sci_pool_put(controller->timer_pool, timer++);
	}

	sci_pool_initialize(controller->unmap_buffer_pool);
}