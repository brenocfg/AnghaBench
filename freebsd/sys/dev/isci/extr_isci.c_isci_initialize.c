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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_2__ {struct ISCI_CONTROLLER* ich_arg; int /*<<< orphan*/ * ich_func; } ;
struct isci_softc {int coalesce_number; int coalesce_timeout; int controller_count; TYPE_1__ config_hook; struct ISCI_CONTROLLER* controllers; int /*<<< orphan*/  sci_library_handle; int /*<<< orphan*/  oem_parameters_found; int /*<<< orphan*/  pci_common_header; int /*<<< orphan*/  device; int /*<<< orphan*/  sci_library_memory; } ;
struct ISCI_CONTROLLER {int index; int /*<<< orphan*/  scif_controller_handle; } ;
typedef  int /*<<< orphan*/  SCI_CONTROLLER_HANDLE_T ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  M_ISCI ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int SCIC_LOG_OBJECT_COMPLETION_QUEUE ; 
 int SCIC_LOG_OBJECT_CONTROLLER ; 
 int SCIC_LOG_OBJECT_SMP_IO_REQUEST ; 
 int SCIC_LOG_OBJECT_SSP_IO_REQUEST ; 
 int SCIC_LOG_OBJECT_STP_IO_REQUEST ; 
 int SCIF_LOG_OBJECT_CONTROLLER ; 
 int SCIF_LOG_OBJECT_IO_REQUEST ; 
 int SCI_LOG_VERBOSITY_ERROR ; 
 int SCI_LOG_VERBOSITY_INFO ; 
 int SCI_LOG_VERBOSITY_TRACE ; 
 int SCI_LOG_VERBOSITY_WARNING ; 
 int /*<<< orphan*/  SCI_MAX_CONTROLLERS ; 
 int SCI_SUCCESS ; 
 int /*<<< orphan*/  TUNABLE_INT_FETCH (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ config_intrhook_establish (TYPE_1__*) ; 
 int /*<<< orphan*/  g_isci_debug_level ; 
 int isci_controller_allocate_memory (struct ISCI_CONTROLLER*) ; 
 int /*<<< orphan*/  isci_controller_construct (struct ISCI_CONTROLLER*,struct isci_softc*) ; 
 int isci_controller_initialize (struct ISCI_CONTROLLER*) ; 
 int /*<<< orphan*/  isci_controller_start ; 
 int /*<<< orphan*/  isci_get_oem_parameters (struct isci_softc*) ; 
 int /*<<< orphan*/  isci_log_message (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  malloc (int,int /*<<< orphan*/ ,int) ; 
 int pci_read_config (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sci_logger_enable (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sci_object_get_logger (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_object_set_association (int /*<<< orphan*/ ,void*) ; 
 int scic_library_get_pci_device_controller_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_library_set_pci_info (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scif_controller_set_interrupt_coalescence (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  scif_library_construct (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int scif_library_get_object_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scif_library_get_scic_handle (int /*<<< orphan*/ ) ; 

int
isci_initialize(struct isci_softc *isci)
{
	int error;
	uint32_t status = 0;
	uint32_t library_object_size;
	uint32_t verbosity_mask;
	uint32_t scic_log_object_mask;
	uint32_t scif_log_object_mask;
	uint8_t *header_buffer;

	library_object_size = scif_library_get_object_size(SCI_MAX_CONTROLLERS);

	isci->sci_library_memory =
	    malloc(library_object_size, M_ISCI, M_NOWAIT | M_ZERO );

	isci->sci_library_handle = scif_library_construct(
	    isci->sci_library_memory, SCI_MAX_CONTROLLERS);

	sci_object_set_association( isci->sci_library_handle, (void *)isci);

	verbosity_mask = (1<<SCI_LOG_VERBOSITY_ERROR) |
	    (1<<SCI_LOG_VERBOSITY_WARNING) | (1<<SCI_LOG_VERBOSITY_INFO) |
	    (1<<SCI_LOG_VERBOSITY_TRACE);

	scic_log_object_mask = 0xFFFFFFFF;
	scic_log_object_mask &= ~SCIC_LOG_OBJECT_COMPLETION_QUEUE;
	scic_log_object_mask &= ~SCIC_LOG_OBJECT_SSP_IO_REQUEST;
	scic_log_object_mask &= ~SCIC_LOG_OBJECT_STP_IO_REQUEST;
	scic_log_object_mask &= ~SCIC_LOG_OBJECT_SMP_IO_REQUEST;
	scic_log_object_mask &= ~SCIC_LOG_OBJECT_CONTROLLER;

	scif_log_object_mask = 0xFFFFFFFF;
	scif_log_object_mask &= ~SCIF_LOG_OBJECT_CONTROLLER;
	scif_log_object_mask &= ~SCIF_LOG_OBJECT_IO_REQUEST;

	TUNABLE_INT_FETCH("hw.isci.debug_level", &g_isci_debug_level);

	sci_logger_enable(sci_object_get_logger(isci->sci_library_handle),
	    scif_log_object_mask, verbosity_mask);

	sci_logger_enable(sci_object_get_logger(
	    scif_library_get_scic_handle(isci->sci_library_handle)),
	    scic_log_object_mask, verbosity_mask);

	header_buffer = (uint8_t *)&isci->pci_common_header;
	for (uint8_t i = 0; i < sizeof(isci->pci_common_header); i++)
		header_buffer[i] = pci_read_config(isci->device, i, 1);

	scic_library_set_pci_info(
	    scif_library_get_scic_handle(isci->sci_library_handle),
	    &isci->pci_common_header);

	isci->oem_parameters_found = FALSE;

	isci_get_oem_parameters(isci);

	/* trigger interrupt if 32 completions occur before timeout expires */
	isci->coalesce_number = 32;

	/* trigger interrupt if 2 microseconds elapse after a completion occurs,
	 *  regardless if "coalesce_number" completions have occurred
	 */
	isci->coalesce_timeout = 2;

	isci->controller_count = scic_library_get_pci_device_controller_count(
	    scif_library_get_scic_handle(isci->sci_library_handle));

	for (int index = 0; index < isci->controller_count; index++) {
		struct ISCI_CONTROLLER *controller = &isci->controllers[index];
		SCI_CONTROLLER_HANDLE_T scif_controller_handle;

		controller->index = index;
		isci_controller_construct(controller, isci);

		scif_controller_handle = controller->scif_controller_handle;

		status = isci_controller_initialize(controller);

		if(status != SCI_SUCCESS) {
			isci_log_message(0, "ISCI",
			    "isci_controller_initialize FAILED: %x\n",
			    status);
			return (status);
		}

		error = isci_controller_allocate_memory(controller);

		if (error != 0)
			return (error);

		scif_controller_set_interrupt_coalescence(
		    scif_controller_handle, isci->coalesce_number,
		    isci->coalesce_timeout);
	}

	/* FreeBSD provides us a hook to ensure we get a chance to start
	 *  our controllers and complete initial domain discovery before
	 *  it searches for the boot device.  Once we're done, we'll
	 *  disestablish the hook, signaling the kernel that is can proceed
	 *  with the boot process.
	 */
	isci->config_hook.ich_func = &isci_controller_start;
	isci->config_hook.ich_arg = &isci->controllers[0];

	if (config_intrhook_establish(&isci->config_hook) != 0)
		isci_log_message(0, "ISCI",
		    "config_intrhook_establish failed!\n");

	return (status);
}